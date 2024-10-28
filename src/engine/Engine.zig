const std: type = @import("std");
const window: type = @import("Renderer/Window.zig");
pub fn Run() void {
    //create main loop here
    Start();

    UpdateLoop();
    //start multithread
    PhysicsUpdate();
    InputUpdate();
    //end multithread

}

fn Start() void {
    window.createWindow("Mordred Engine", 1280, 720);
}

fn UpdateLoop() void {
    //contains both Update functions and render functions
}

fn PreUpdate() void {
    //fired before update
}

fn Update() void {
    //fired before rendering
}

fn PostUpdate() void {
    //fired after rendering
}

fn PhysicsUpdate() void {}

fn InputUpdate() void {}
