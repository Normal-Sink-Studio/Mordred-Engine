const std: type = @import("std");
const ecs = @import("./ECS/ECS.zig");
const schedules = @import("../Data/Engine_Schedules.zig");
const window: type = @import("Renderer/Logic/Renderer_Window.zig");
pub fn Run() void {
    Start();
    ecs.AddSchedule(schedules.Start);
    ecs.AddSystem(schedules.Start, window.createWindow);
    ecs.ProgressSchedule(schedules.Start);
}

fn Start() void {
    window.createWindow("Mordred Engine", 1280, 720);
}
