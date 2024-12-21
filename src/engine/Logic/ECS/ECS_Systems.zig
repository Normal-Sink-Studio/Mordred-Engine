const std = @import("std");
const schedules = @import("../../Data/Engine_Schedules.zig");
const allocatorManager = @import("../Memory/AllocatorManager.zig");

const allocator = allocatorManager.getAllocator();
pub const Schedule = struct {
    systems: std.ArrayListUnmanaged(*const fn () void),
};

pub fn NewSchedule() Schedule {
    return Schedule{
        .systems = std.ArrayListUnmanaged(*const fn () void){},
    };
}

pub fn addSystem(schedule: *Schedule, system: *const fn () void) void {
    schedule.systems.append(allocator, system) catch |err| {
        std.debug.print("ERROR: {}\n", .{err});
        schedule.systems.deinit(allocator);
    };
}
pub fn Progress(schedule: *Schedule) void {
    const length = schedule.systems.items.len;
    var i: u32 = 0;
    while (i < length) {
        const func = schedule.systems.items[i];
        func();
        i += 1;
    }
}

pub fn clearSchedule(schedule: * Schedule) void {
    schedule.systems.deinit(allocator);
}
