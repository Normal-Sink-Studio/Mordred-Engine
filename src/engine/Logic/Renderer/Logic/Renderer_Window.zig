const c = @cImport({
    @cInclude("GLFW/glfw3.h");
});
const std = @import("std");
const engine = @import("../../Engine.zig");
const world = @import("../../ECS/ECS_World.zig");

pub var glWindow: *c.GLFWwindow = undefined;

pub fn createWindow(windowName: [*c]const u8, Width: i32, Height: i32) void {
// Set the GLFW error callback

    if (c.glfwInit() == 0) {
        std.debug.print("ERROR: GLFW Initialization Failed", .{});
        return;
    }

    glWindow = c.glfwCreateWindow(Width, Height, windowName, null, null) orelse {
        // Handle window creation error
        std.debug.print("ERROR: Window Creation Failed", .{});
        return;
    };
    _ = c.glfwSetWindowCloseCallback(glWindow, onWindowClose);

    while (c.glfwWindowShouldClose(glWindow) == 0) {
        c.glfwPollEvents();
    }
}

fn onWindowClose(_: ?*c.GLFWwindow) callconv(.C) void{
    engine.cleanUp();
}
