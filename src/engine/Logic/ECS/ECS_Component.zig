const Schedules: type = @import("../../Data/Engine_Schedules.zig");

pub fn addComponent(comptime T: type) !void {
    //const componentType = @TypeOf(T);

    if (@typeInfo(T) != .Struct) {
        @compileError("ERROR: TYPE IS NOT A SCHEDULE");
    }

    // Additional code to handle the component can go here
}
