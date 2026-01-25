# System Requirements

## Minimum Requirements

### Operating System
- **For running games:** Windows 95 (with proper configuration)
- **For development:** Windows Vista with Service Pack 2

### Storage
- **50 MB** of free disk space

### Processor
- **Intel Pentium 4** or equivalent (1.5 GHz minimum)
- **Single-core CPU with SSE2 support**

### Memory
- **256 MB RAM** (512 MB recommended for development)

---

## Recommended Requirements

### Operating System
- Windows 7 or newer

### Storage
- **200 MB** of free disk space

### Processor
- **Intel Core i7 3rd generation** or equivalent
- **Multi-core CPU recommended** (2+ cores)
- Engine performance scales with CPU power as all rendering is processor-based

### Memory
- **2 GB RAM** or more
- Additional memory improves complex scene handling

---

# Technical Notes

## CPU-Exclusive Rendering
Dolphin3D performs all graphics calculations on the CPU, without GPU acceleration. This means:
- Performance directly correlates with processor speed and core count
- Integrated or discrete graphics cards do not affect rendering speed
- Older systems require capable CPUs despite minimal OS requirements

## Windows 95 Compatibility
While theoretically compatible with Windows 95, practical use requires:
- CPU with adequate single-thread performance (Pentium 4 or better)
- Proper application manifest configuration
- Potential adjustments for legacy API support

---

# Language Standards

## Minimum Supported
- **C**: C99 standard
- **C++**: C++98 standard

## Recommended
- **C**: C99 or newer
- **C++**: C++03 standard

---

# Development Software

## Recommended IDE
- **Visual Studio C++ 2008** (or higher)
- **CMake 3.0+**

> **Migration Notice:**  
> Projects created in Visual Studio 2008 can be migrated to newer versions.
> Also, the use of other IDE does not guarantee the operation of the engine.
>
> ⚠️ **Performance Consideration:**  
> The engine's CPU-bound nature means adequate processor power is essential. Even simple scenes may struggle on legacy single-core systems despite meeting minimum OS requirements.
