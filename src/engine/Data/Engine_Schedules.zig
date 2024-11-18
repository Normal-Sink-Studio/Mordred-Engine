const systems = @import("../Logic/ECS/ECS_Systems.zig");

pub const Start = systems.NewSchedule();

pub const PreUpdate = systems.NewSchedule();

pub const Update = systems.NewSchedule();

pub const PostUpdate = systems.NewSchedule();

pub const FixedUpdate = systems.NewSchedule();

pub const InputUpdate = systems.NewSchedule();
