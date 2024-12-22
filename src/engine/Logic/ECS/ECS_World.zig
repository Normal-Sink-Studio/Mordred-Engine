const std = @import("std");
const allocatorManager = @import("../Memory/AllocatorManager.zig");
const pageSize: u8 = 5;

pub const Enity: u32 = 0;

const allocator = allocatorManager.getAllocator();
var idStack = std.ArrayListUnmanaged(u32){};
var entities : std.DynamicBitSetUnmanaged = .{};
var ID: u32 = 0;

pub fn spawnEntity() u32 {
    if (entities.count() != 0){
        entities.resize(allocator, 2, true) catch |err| { //add ID to the idStack
        std.debug.print("ERROR: {}\n", .{err});
        } ;
    }
    std.debug.print("Bitset Length is now {}\n", .{entities.count()});
    if (idStack.items.len == 0) {
        const id: u32 = ID;
        ID += 1;
        std.debug.print("Spawning Entity {}\n", .{id});
        return id;
    } else {
        const id: u32 = idStack.pop();
        std.debug.print("Spawning Entity {}\n", .{id});
        return id;
    }
}

pub fn deleteEntity(Entity: u32) void {
    //remove from entity list
    std.debug.print("Removing Entity {} from list\n", .{Entity});
    idStack.append(allocator, Entity) catch |err| { //add ID to the idStack
        std.debug.print("ERROR: {}\n", .{err});
    };
    std.debug.print("Unused ID Count: {}\n", .{idStack.items.len});
}

pub fn deinit() void {
    // var iter = Scenes.valueIterator();
    //while(iter.next())|value_ptr|{
    //  const Entities = value_ptr.*;
    // }
    // Scenes.deinit();
    idStack.deinit(allocator);
}
