const std: type = @import("std");
const ecs = @import("./ECS/ECS.zig");
const world = @import("./ECS/ECS_World.zig");
const schedules = @import("../Data/Engine_Schedules.zig");
const systems = @import("../Logic/ECS/ECS_Systems.zig");
const window: type = @import("Renderer/Logic/Renderer_Window.zig");

pub fn Setup() void {
    Run();
}

pub fn Run() void {
    Start();
}

fn Start() void {
    window.createWindow("Mordred Engine", 1280, 720);
}
