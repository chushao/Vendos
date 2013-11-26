using Microsoft.Kinect;
using System;

namespace Fizbin.Kinect.Gestures.Segments
{
    /// <summary>
    /// The third part of the swipe down gesture for the right hand
    /// </summary>
    public class SwipeDownSegment3 : IRelativeGestureSegment
    {
        /// <summary>
        /// Checks the gesture.
        /// </summary>
        /// <param name="skeleton">The skeleton.</param>
        /// <returns>GesturePartResult based on if the gesture part has been completed</returns>
        public GesturePartResult CheckGesture(Skeleton skeleton)
        {
            // //Right hand in front of right Shoulder
            if (/*skeleton.Joints[JointType.HandRight].Position.Z < skeleton.Joints[JointType.ElbowRight].Position.Z &&*/ skeleton.Joints[JointType.HandRight].Position.Y < skeleton.Joints[JointType.ShoulderCenter].Position.Y)
            {
                //Console.WriteLine("Swipe Down 3 - 1");

                // right hand below hip
                if (skeleton.Joints[JointType.HandRight].Position.Y < skeleton.Joints[JointType.HipRight].Position.Y)
                {
                    //Console.WriteLine("Swipe Down 3 - 2");

                    // right hand right of center hip
                    if (skeleton.Joints[JointType.HandRight].Position.X > skeleton.Joints[JointType.HipCenter].Position.X)
                    {
                       //Console.WriteLine("Swipe Down 3 - Success");

                        return GesturePartResult.Succeed;
                    }
                    //Console.WriteLine("Swipe Down 3 - Pausing");

                    return GesturePartResult.Pausing;
                }
                //Console.WriteLine("Swipe Down 3 - Fail");

                // Debug.WriteLine("GesturePart 2 - right hand below shoulder height but above hip height - FAIL");
                return GesturePartResult.Fail;
            }

            // Debug.WriteLine("GesturePart 2 - Right hand in front of right Shoulder - FAIL");
            return GesturePartResult.Fail;
        }
    }
}