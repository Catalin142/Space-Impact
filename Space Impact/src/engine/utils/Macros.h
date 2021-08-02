#pragma once

#define SAFE_RELEASE(T) if (T != nullptr) {T->Release(); T = nullptr; }

#define VK_W 0x57
#define VK_S 0x53