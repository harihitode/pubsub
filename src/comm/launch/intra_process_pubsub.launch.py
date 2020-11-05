import launch
import launch_ros.actions

def generate_launch_description():
    arguments = launch.actions.DeclareLaunchArgument(
        'blob_size',
        default_value=['1000'],
        description='blob data size; default 1000 [Byte]'
    )

    pubsub = launch_ros.actions.Node(
        package='comm',
        node_executable='pubsub',
        output='log',
        parameters=[{'blob_size':launch.substitutions.LaunchConfiguration('blob_size')}]
    )

    return launch.LaunchDescription([
        arguments,
        pubsub,
    ])
