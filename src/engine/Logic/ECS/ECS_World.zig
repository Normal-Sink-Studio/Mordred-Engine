const std = @import("std");
const allocatorManager = @import("../Memory/AllocatorManager.zig");

pub const Enity: u32 = 0;

const allocator = allocatorManager.getAllocator();
var entities : std.DynamicBitSetUnmanaged = .{};

//Entity Logic
pub fn spawnEntity() u32 {
    //iterate through the Entity List to check for the first unused bit otherwise add a new bit to the bitset
    if(entities.bit_length != 0){
        var i: u32 = 0;
        while(i < entities.bit_length)
        {
            std.debug.print("Iter at {}\n", .{i});
            if(!entities.isSet(i)){
                entities.set(i);
                std.debug.print("Spawning Entity {}\n", .{i});
                return @intCast(i);
            }
            i += 1;
        }
        entities.resize(allocator, entities.bit_length + 1, true) catch |err| { 
            std.debug.print("ERROR: {}\n", .{err});
            
        } ;
        std.debug.print("Spawning Entity {}\n", .{entities.bit_length - 1});
        return @intCast(entities.bit_length - 1);
    }
    else{
        entities.resize(allocator, 1, true) catch |err| {
            std.debug.print("ERROR: {}\n", .{err});
        } ;
        std.debug.print("Spawning Entity {}\n", .{0});
        return 0;
    }
}

pub fn deleteEntity(Entity: u32) void {
    //remove from entity list
    entities.unset(Entity);
    std.debug.print("Removing Entity {} from list\n", .{Entity});
}

pub fn deinit() void {
    entities.deinit(allocator);
}

//Component Logic

const SparseSet = struct {
    //create sparse list
    sparseList: std.ArrayListUnmanaged([5]u32),
    //create dense list
    denseList: std.ArrayListUnmanaged(type)
};

pub fn newComponent(_: type) void {
    //check to make sure component is of type struct
    //create Sparse Set for the component's data
    //store the sparse set somehow
}
