//This file is a wrapper for everything else in the ECS
const Component: type = @import("ECS_Component.zig");
const Entity: type = @import("ECS_Entity.zig");
const World: type = @import("ECS_World.zig");
const Schedules: type = @import("../../Data/Engine_Schedules.zig");

usingnamespace Component;
usingnamespace Entity;
usingnamespace World;

pub fn AddSchedule(T: type) void {
    try World.addSchedule(T);
}

pub fn ProgressSchedule(_: type) void {}

pub fn AddSystem(T: *type, function: *fn () void) void {
    World.addSystem(T, function);
}

pub fn AddComponent(T: *type) void {
    try Component.addComponent(T);
}

pub fn SpawnEntity() void {
    Entity.spawnEntity().addComponent();
}
