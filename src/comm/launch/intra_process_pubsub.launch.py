import launch
import launch_ros.actions

BLOB_SIZE = 2000;

def generate_launch_description():
    pubsub = launch_ros.actions.Node(
        package='comm',
        node_executable='pubsub',
        output='screen',
        parameters=[{'blob_size':BLOB_SIZE}]
    )

    return launch.LaunchDescription([
        pubsub,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=pubsub,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )),
    ])
