const ecs = @import("../ECS/ECS.zig");
const engine_schedules = @import("Data/Engine_Schedules.zig");
const components = @import("Data/Renderer_Components.zig");

pub fn init() void {
    ecs.AddComponent(components.WGPU_Renderer);
}
