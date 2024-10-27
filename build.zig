const std = @import("std");

// The build function configures the build process for the Mordred-Engine project.
pub fn build(b: *std.Build) void {
    // Create an executable target with the name "Mordred-Engine"
    // The main source file is located at "src/main.zig"
    // The target platform is the host platform.
    const exe = b.addExecutable(.{
        .name = "Mordred-Engine",
        .root_source_file = b.path("src/main.zig"),
        .target = b.host,
    });

    // Define the path to the GLEW library and its headers
    const GLEW_Path = b.path("dependencies/GLEW/glew-2.1.0/lib/");
    const GLEW_Headers = b.path("dependecies/GLEW/glew-2.1.0/include");

    // Add the GLEW headers to the include path
    exe.addIncludePath(GLEW_Headers);
    // Link the GLEW library by adding it to the library path
    exe.addLibraryPath(GLEW_Path);

    exe.linkSystemLibrary("glew32s");

    // Define the path to the GLFW library and its headers
    const GLFW_Path = b.path("dependencies/GLFW/lib-vc2022/");
    const GLFW_Headers = b.path("dependencies/GLFW/include/");

    exe.linkSystemLibrary("c");
    exe.linkSystemLibrary("user32");
    exe.linkSystemLibrary("gdi32");
    exe.linkSystemLibrary("shell32");

    // Add the GLFW headers to the include path
    exe.addIncludePath(GLFW_Headers);
    // Link the GLFW library by adding it to the library path
    exe.addLibraryPath(GLFW_Path);

    exe.linkSystemLibrary("glfw3");

    // Mark the executable as an installable artifact
    b.installArtifact(exe);
}
