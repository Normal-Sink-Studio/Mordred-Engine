const std = @import("std");

// The build function configures the build process for the Mordred-Engine project.
pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    if (target.result.os.tag == .windows and target.result.abi != .msvc) {
        std.log.err("Target ABI must be msvc when targeting Windows, try zig build -Dtarget=x86_64-windows-msvc", .{});
        std.process.exit(1); // or return; if you don't want to exit with error code 1
    }

    // Create an executable target with the name "Mordred-Engine"
    // The main source file is located at "src/main.zig"
    // The target platform is the host platform.
    const exe = b.addExecutable(.{
        .name = "Mordred-Engine",
        .root_source_file = b.path("src/main.zig"),
        .target = target,
    });

    // Define the path to the GLFW library and its headers

    exe.linkLibC();
    exe.linkSystemLibrary("user32");
    exe.linkSystemLibrary("gdi32");
    exe.linkSystemLibrary("shell32");

    // Specify libraries to link against

    const GLFW_Path = b.path("dependencies/windows/x86_64/GLFW/lib-vc2022/");
    const GLFW_Headers = b.path("dependencies/windows/x86_64/GLFW/include/");
    // Add the GLFW headers to the include path
    exe.addIncludePath(GLFW_Headers);
    // Link the GLFW library by adding it to the library path
    exe.addLibraryPath(GLFW_Path);

    exe.linkSystemLibrary("glfw3");

    const WGPU_Path = b.path("dependencies/windows/x86_64/WGPU/lib/");
    const WGPU_Headers = b.path("dependencies/windows/x86_64/WGPU/include/");

    exe.addIncludePath(WGPU_Headers);

    exe.addLibraryPath(WGPU_Path);

    exe.linkSystemLibrary("wgpu_native");
    // Mark the executable as an installable artifact

    b.installArtifact(exe);

    // This *creates* a Run step in the build graph, to be executed when another
// step is evaluated that depends on it. The next line below will establish
// such a dependency.
    const run_cmd = b.addRunArtifact(exe);

    // By making the run step depend on the install step, it will be run from the
    // installation directory rather than directly from within the cache directory.
    // This is not necessary, however, if the application depends on other installed
    // files, this ensures they will be present and in the expected location.
    run_cmd.step.dependOn(b.getInstallStep());


    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
