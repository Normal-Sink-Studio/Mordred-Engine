//This file is a wrapper for everything else in the ECS
const Component: type = @import("./Component.zig");
const Entity: type = @import("./Entity.zig");
const World: type = @import("World.zig");

usingnamespace Component;
usingnamespace Entity;
usingnamespace World;

pub const Schedule = struct {};

pub fn AddSchedule(_: Schedule) void {}

pub fn ProgressSchedule(_: Schedule) void {}

pub fn AddSystem(_: Schedule, _: fn () void) void {}

pub fn AddComponent(component: anytype) !void {
    if (@TypeOf(component) != struct {}) {
        @compileError("ERROR: INVALID COMPONENT TYPE");
    }
}

pub fn SpawnEntity() void {
    Entity.spawnEntity();
}
