const std = @import("std");
const schedules = @import("../../Data/Engine_Schedules.zig");

pub const Schedule = struct {
    systems: std.ArrayList(*const fn () void),
};

pub fn NewSchedule() Schedule {
    const allocator = getAllocator();
    return Schedule{
        .systems = std.ArrayList(*const fn () void).init(allocator),
    };
}

pub fn addSystem(schedule: *Schedule, system: *const fn () void) void {
    try schedule.systems.append(system) catch std.debug.print("ERROR: FAILED TO ADD SYSTEM\n", {});
}

pub fn Progress(_: *Schedule) void {}

// AllocatorManager struct
pub const AllocatorManager = struct {
    gpa: std.heap.GeneralPurposeAllocator(.{}),
};

// AllocatorManager functions
pub fn AllocatorManager_init() void {
    const instance = AllocatorManager_getInstance();
    instance.gpa = std.heap.GeneralPurposeAllocator(.{}){};
}

pub fn AllocatorManager_deinit() void {
    const instance = AllocatorManager_getInstance();
    instance.gpa.deinit();
}

pub fn getAllocator() std.mem.Allocator {
    return AllocatorManager_getInstance().gpa.allocator();
}

fn AllocatorManager_getInstance() *AllocatorManager {
    return &globalInstance;
}

// Global AllocatorManager instance
var globalInstance: AllocatorManager = undefined;
