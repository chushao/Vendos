using Microsoft.Kinect;
using System;

namespace Fizbin.Kinect.Gestures.Segments
{
    /// <summary>
    /// The second part of the swipe down gesture for the right hand
    /// </summary>
    public class SwipeDownSegment2 : IRelativeGestureSegment
    {
        /// <summary>
        /// Checks the gesture.
        /// </summary>
        /// <param name="skeleton">The skeleton.</param>
        /// <returns>GesturePartResult based on if the gesture part has been completed</returns>
        public GesturePartResult CheckGesture(Skeleton skeleton)
        {
            // right hand in front of right shoulder
            if (/*skeleton.Joints[JointType.HandRight].Position.Z < skeleton.Joints[JointType.ShoulderRight].Position.Z && */skeleton.Joints[JointType.HandRight].Position.Y < skeleton.Joints[JointType.ShoulderCenter].Position.Y)
            {
                //Console.WriteLine("Swipe Down 2 - 1");

                // right hand below right elbow
                if (skeleton.Joints[JointType.HandRight].Position.Y < skeleton.Joints[JointType.ElbowRight].Position.Y)
                {
                    //Console.WriteLine("Swipe Down 2 - 2");

                    // right hand right of right shoulder
                    if (skeleton.Joints[JointType.HandRight].Position.X > skeleton.Joints[JointType.HipCenter].Position.X)
                    {
                        //Console.WriteLine("Swipe Down 2 - Success");

                        return GesturePartResult.Succeed;
                    }
                    //Console.WriteLine("Swipe Down 2 - Pausing");

                    return GesturePartResult.Pausing;
                }
                //Console.WriteLine("Swipe Down 2 - Fail");

                return GesturePartResult.Fail;
            }
            return GesturePartResult.Fail;
        }
    }
}