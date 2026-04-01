#pragma once

#include <windows.h>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstring>

class MemoryMappedFile {
public:
    MemoryMappedFile() = default;
    ~MemoryMappedFile() {
        close();
    }

    // 禁拷贝
    MemoryMappedFile(const MemoryMappedFile&) = delete;
    MemoryMappedFile& operator=(const MemoryMappedFile&) = delete;

    // 允许移动
    MemoryMappedFile(MemoryMappedFile&& other) noexcept {
        moveFrom(std::move(other));
    }
    MemoryMappedFile& operator=(MemoryMappedFile&& other) noexcept {
        if (this != &other) {
            close();
            moveFrom(std::move(other));
        }
        return *this;
    }

    // 打开并映射文件（只读）
    void open(const std::string& path) {
        close();

        hFile_ = CreateFileA(
            path.c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
        if (hFile_ == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("CreateFile failed");
        }

        LARGE_INTEGER sz;
        if (!GetFileSizeEx(hFile_, &sz)) {
            close();
            throw std::runtime_error("GetFileSizeEx failed");
        }
        fileSize_ = static_cast<uint64_t>(sz.QuadPart);

        hMap_ = CreateFileMappingA(
            hFile_,
            nullptr,
            PAGE_READONLY,
            0,
            0,
            nullptr
        );
        if (!hMap_) {
            close();
            throw std::runtime_error("CreateFileMapping failed");
        }

        base_ = static_cast<const char*>(
            MapViewOfFile(
                hMap_,
                FILE_MAP_READ,
                0,
                0,
                0
            )
        );
        if (!base_) {
            close();
            throw std::runtime_error("MapViewOfFile failed");
        }
    }

    void close() {
        if (base_) {
            UnmapViewOfFile(base_);
            base_ = nullptr;
        }
        if (hMap_) {
            CloseHandle(hMap_);
            hMap_ = nullptr;
        }
        if (hFile_ != INVALID_HANDLE_VALUE) {
            CloseHandle(hFile_);
            hFile_ = INVALID_HANDLE_VALUE;
        }
        fileSize_ = 0;
    }

    bool isOpen() const {
        return base_ != nullptr;
    }

    uint64_t size() const {
        return fileSize_;
    }

    const char* base() const {
        return base_;
    }

    // ===============================
    // 核心接口：读取一段数据
    // ===============================
    void read(uint64_t logicalOffset, void* dst, uint64_t bytes) const {
        if (!base_) {
            throw std::runtime_error("MemoryMappedFile not open");
        }
        if (bytes == 0) return;

        uint64_t fileOffset = logicalOffset % fileSize_;

        if (fileOffset + bytes <= fileSize_) {
            // 不跨文件尾
            std::memcpy(dst, base_ + fileOffset, static_cast<size_t>(bytes));
        } else {
            // 跨文件尾（rare path）
            uint64_t firstPart = fileSize_ - fileOffset;
            std::memcpy(dst, base_ + fileOffset, static_cast<size_t>(firstPart));
            std::memcpy(
                static_cast<char*>(dst) + firstPart,
                base_,
                static_cast<size_t>(bytes - firstPart)
            );
        }
    }

private:
    void moveFrom(MemoryMappedFile&& other) noexcept {
        hFile_ = other.hFile_;
        hMap_ = other.hMap_;
        base_ = other.base_;
        fileSize_ = other.fileSize_;

        other.hFile_ = INVALID_HANDLE_VALUE;
        other.hMap_ = nullptr;
        other.base_ = nullptr;
        other.fileSize_ = 0;
    }

private:
    HANDLE hFile_ = INVALID_HANDLE_VALUE;
    HANDLE hMap_ = nullptr;
    const char* base_ = nullptr;
    uint64_t fileSize_ = 0;
};
