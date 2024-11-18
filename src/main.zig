const Engine: type = @import("engine/Logic/Engine.zig");
const ECS: type = @import("engine/Logic/ECS/ECS.zig");

const test2 = struct { test3: i32 };

pub fn main() void {
    Engine.Setup();
}
