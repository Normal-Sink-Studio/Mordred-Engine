const c = @cImport({
    //@cInclude("GLFW/glfw3.h");
    @cInclude("GLFW/glfw3.h");
});
const World = @import("../../ECS/ECS_World.zig");

pub const WGPU_Renderer = struct {
    pub var glWindow: *c.GLFWwindow = null;
};

pub const window = Component(.{
    pub var glWindow: *c.GLFWwindow = null;
});
