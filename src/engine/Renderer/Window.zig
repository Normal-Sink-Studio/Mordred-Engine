const Window = struct {};

const c = @cImport({
    @cInclude("GL/gl.h");
    @cInclude("GLFW/glfw3.h");
});

pub var glWindow: *c.GLFWwindow = undefined;

pub fn createWindow(windowName: [*c]const u8, Width: i32, Height: i32) void {
    if (c.glfwInit() == c.GL_FALSE) {
        // Handle error appropriately
        return;
    }
    glWindow = c.glfwCreateWindow(Width, Height, windowName, null, null) orelse {
        // Handle window creation error
        return;
    };
}
