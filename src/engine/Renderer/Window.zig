const c = @cImport({
    @cInclude("GLFW/glfw3.h");
});
const std = @import("std");

pub var glWindow: *c.GLFWwindow = undefined;

pub fn createWindow(windowName: [*c]const u8, Width: i32, Height: i32) void {
    if (c.glfwInit() != c.GL_TRUE) {
        return;
    }

    glWindow = c.glfwCreateWindow(Width, Height, windowName, null, null) orelse {
        // Handle window creation error
        std.debug.print("ERROR: Window Creation Failed", .{});
        return;
    };

    while (c.glfwWindowShouldClose(glWindow) == 0) {
        c.glfwPollEvents();
    }
}
