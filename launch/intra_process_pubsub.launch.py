import launch
import launch_ros.actions

def generate_launch_description():
    pubsub = launch_ros.actions.Node(
        package='comm',
        node_executable='pubsub',
        output='screen'
    )

    return launch.LaunchDescription([
        pubsub,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=pubsub,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )),
    ])
