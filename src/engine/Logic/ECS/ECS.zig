//This file is a wrapper for everything else in the ECS
const World: type = @import("ECS_World.zig");
const Schedules: type = @import("../../Data/Engine_Schedules.zig");


pub fn AddSchedule() void {
    try World.addSchedule();
}

pub fn ProgressSchedule(_: *type) void {}

pub fn AddSystem(schedule: struct {}, system: fn () void) void {
    World.addSystem(schedule, system);
}


