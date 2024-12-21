const std = @import("std");

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
    _ = instance.gpa.deinit();
}

pub fn getAllocator() std.mem.Allocator {
    return AllocatorManager_getInstance().gpa.allocator();
}

fn AllocatorManager_getInstance() *AllocatorManager {
    return &globalInstance;
}

// Global AllocatorManager instance
var globalInstance: AllocatorManager = undefined;
