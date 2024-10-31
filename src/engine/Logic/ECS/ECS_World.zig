pub fn addSchedule(comptime T: type) !void {
    if (@typeInfo(T) != .Struct) {
        @compileError("ERROR: INVALID COMPONENT TYPE");
    }
}

pub fn progressSchedule(comptime T: type) !void {
    if (@typeInfo(T) != .Struct) {
        @compileError("ERROR: INVALID COMPONENT TYPE");
    }
}

pub fn addSystem(_: type, _: fn () void) void {}
