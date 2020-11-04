import launch
import launch_ros.actions

def generate_launch_description():
    publisher = launch_ros.actions.Node(
        package='comm',
        node_executable='publisher',
        output='screen'
    )
    subscriber = launch_ros.actions.Node(
        package='comm',
        node_executable='subscriber',
        output='screen'
    )

    return launch.LaunchDescription([
        publisher,
        subscriber,
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=publisher,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )),
    ])
