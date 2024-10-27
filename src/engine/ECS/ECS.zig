pub const Schedule = struct {};

pub fn AddSchedule(_: Schedule) void {}

pub fn ProgressSchedule(_: Schedule) void {}

pub fn AddSystem(_: Schedule, _: fn () void) void {}
