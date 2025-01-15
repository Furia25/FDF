# 🌐 FDF - Wireframe

![Project Logo](https://github.com/user-attachments/assets/528eccd4-228c-46a0-9619-6b8a35bf706c)

## 📋 Table of Contents

- [📖 Introduction](#introduction)
- [✨ Unique Features](#unique-features)
- [🚀 Usage](#usage)
- [📜 License](#license)

---

## 📖 Introduction

**FIL DE FER - WIREFRAME** is a project focused on rendering 3D wireframe models from `.fdf` files.

---

## ✨ Unique Features

- **True 3D Projection**: The `fdf` projection simulates real 3D, complete with various types of rasterization. However, this realism might introduce performance issues due to the lack of optimizations.
- **Three Display Modes**:
  - **Mode 0**: Polygons 🟩
  - **Mode 1**: Points 🔵
  - **Mode 2**: FDF / Wireframe 🕸️

![Mode 0 - Polygons](https://github.com/user-attachments/assets/3e6ca99b-00a9-4ab4-8871-c7a264ea58d6)
> **Note**: Polygons are lag-free if you're far away from them. 😄

![Mode 1 - Points](https://github.com/user-attachments/assets/f1983bd2-d323-4bb6-96f8-4af8088b27f5)

![Mode 2 - Wireframe](https://github.com/user-attachments/assets/155f49fd-074c-4736-b1be-e8c6b0f055d7)
> **Note**: Lines are currently drawn by interpolating points and then projecting them, which is not the most efficient method. A replacement using Bresenham's algorithm is on the way! 🛠️

---

## 🚀 Usage

1. **Compile** the project using the provided Makefile:
2 - Execute the binary created with a file in argument

```bash
./fdf test_maps/mars.fdf
```

## <span style="color:green;">License</span>

This project is licensed under the [MIT License](LICENSE).

