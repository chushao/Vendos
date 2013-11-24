using Microsoft.Kinect;

namespace Fizbin.Kinect.Gestures.Segments
{
    public class RaiseTheRoofSegment1 : IRelativeGestureSegment
    {
         /// <summary>
        /// Checks the gesture.
        /// </summary>
        /// <param name="skeleton">The skeleton.</param>
        /// <returns>GesturePartResult based on if the gesture part has been completed</returns>
        public GesturePartResult CheckGesture(Skeleton skeleton)
        {
            // Left and right hand are higher than shoulders
            if (skeleton.Joints[JointType.HandLeft].Position.Y >= skeleton.Joints[JointType.ShoulderLeft].Position.Y
                && skeleton.Joints[JointType.HandRight].Position.Y >= skeleton.Joints[JointType.ShoulderRight].Position.Y)
            {
                // left and right elbow are less than shoulders
               if (skeleton.Joints[JointType.ElbowLeft].Position.Y < skeleton.Joints[JointType.ShoulderLeft].Position.Y
                   && skeleton.Joints[JointType.ElbowRight].Position.Y < skeleton.Joints[JointType.ShoulderRight].Position.Y)
               {
                    // left hand 0.2 to left of left elbow
                 //   if (skeleton.Joints[JointType.HandLeft].Position.X < skeleton.Joints[JointType.ElbowLeft].Position.X - 0.2)
                  //  {
                        return GesturePartResult.Succeed;
               }

                return GesturePartResult.Pausing;
            }

            return GesturePartResult.Fail;
        }
    }

    public class RaiseTheRoofSegment2 : IRelativeGestureSegment
    {
        /// <summary>
        /// Checks the gesture.
        /// </summary>
        /// <param name="skeleton">The skeleton.</param>
        /// <returns>GesturePartResult based on if the gesture part has been completed</returns>
        public GesturePartResult CheckGesture(Skeleton skeleton)
        {
            // Left hand is higher than left shoulder 
            if (skeleton.Joints[JointType.HandLeft].Position.Y >= skeleton.Joints[JointType.ShoulderLeft].Position.Y
                && skeleton.Joints[JointType.HandRight].Position.Y >= skeleton.Joints[JointType.ShoulderRight].Position.Y)
            {
                // left elbow is above left shoulder
                if (skeleton.Joints[JointType.ElbowLeft].Position.Y >= skeleton.Joints[JointType.ShoulderLeft].Position.Y
                    && skeleton.Joints[JointType.ElbowRight].Position.Y >= skeleton.Joints[JointType.ShoulderRight].Position.Y)
                {
                    // left hand 0.2 to left of left elbow
                    //   if (skeleton.Joints[JointType.HandLeft].Position.X < skeleton.Joints[JointType.ElbowLeft].Position.X - 0.2)
                    //  {
                    return GesturePartResult.Succeed;
                }

                return GesturePartResult.Pausing;
            }

            return GesturePartResult.Fail;
        }
    }
}
