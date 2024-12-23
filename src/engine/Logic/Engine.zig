const std: type = @import("std");
const ecs = @import("./ECS/ECS.zig");
const world = @import("./ECS/ECS_World.zig");
const schedules = @import("../Data/Engine_Schedules.zig");
const systems = @import("../Logic/ECS/ECS_Systems.zig");
const window: type = @import("Renderer/Logic/Renderer_Window.zig");
const allocator = @import("../Logic/Memory/AllocatorManager.zig");

pub fn Init() void {
    allocator.AllocatorManager_init();

    systems.addSystem(&schedules.Start, &Start);
}

pub fn Run() void {
    systems.Progress(&schedules.Start);
}

fn Start() void {
    std.debug.print("Start function\n", .{});
    _ = world.spawnEntity();
    

    window.createWindow("Mordred Engine", 1280, 720);
}

pub fn cleanUp() void
{
    systems.clearSchedule(&schedules.Start);
    systems.clearSchedule(&schedules.Update);
    systems.clearSchedule(&schedules.FixedUpdate);
    systems.clearSchedule(&schedules.PostUpdate);
    systems.clearSchedule(&schedules.InputUpdate);
    world.deinit();
    defer allocator.AllocatorManager_deinit();

    std.debug.print("Closing Application\n", .{});
}
