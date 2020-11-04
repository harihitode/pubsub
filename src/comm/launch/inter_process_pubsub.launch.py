import launch
import launch_ros.actions

def generate_launch_description():
    blob_size = launch.substitutions.LaunchConfiguration('blob_size')
    publisher = launch_ros.actions.Node(
        package='comm',
        node_executable='publisher',
        output='screen',
        parameters=[{'blob_size':blob_size}]
    )
    subscriber = launch_ros.actions.Node(
        package='comm',
        node_executable='subscriber',
        output='screen',
        parameters=[{'blob_size':blob_size}]
    )

    return launch.LaunchDescription([
        publisher,
        subscriber,
        launch.actions.DeclareLaunchArgument(
            'blob_size',
            default_value=['1000'],
            description='blob data size; default 1000 [Byte]'
        ),
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=publisher,
                on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())],
            )),
    ])
