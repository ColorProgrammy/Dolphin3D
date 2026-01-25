# Setting Up Dolphin3D

### Prerequisites

To compile the project, you will need **Visual Studio**.  
It is recommended to use **Visual Studio C++ 2008**, as the engine code was originally developed and tested in this environment.
Or you can use CMake 3.0+ if you don't have an IDE

> **Note for newer versions:**  
> If you are using Visual Studio 2010 or later, you may need to migrate the project. Please be aware that compatibility issues could arise during this process.

---

### Project Configuration

1. **Add files to your project** in Visual Studio.
2. Include the main Dolphin3D library by adding the following path to your project settings:  
   `../include/Dolphin3D.h`
3. Write your application code in `main.cpp`. Refer to the provided documentation and examples for guidance.

---

### Building the Project
**Visual Studio 2008:**
1. In **Solution Explorer**, right-click on your project.
2. Select **Build** from the context menu.
3. Once compiled, your application will be generated in the `bin` folder — provided you have configured the output path accordingly in the project settings.

**CMake 3.0:**
1. Open the build.bat in the engine's folder.
2. Compile the code.
3. Once compiled, your application will be generated in the `bin` folder — provided you have configured the output path accordingly in the project settings.

---

### Project Structure

| Folder     | Purpose                                                                 |
|------------|-------------------------------------------------------------------------|
| `src`      | Contains source code scripts.                                           |
| `include`  | Houses library files required for the engine to function correctly.     |
| `_docs`    | Documentation and helpful guides for using the engine.                  |
| `examples` | Sample projects for reference, testing, and learning.                   |
| `bin`      | Output directory for compiled executables.                              |
| `tools`    | Additional utilities and helper programs.                               |

---

### Next Steps
You are now ready to start developing with Dolphin3D. Explore the examples and documentation to familiarize yourself with the engine’s workflow.

**Good luck with your development!**
