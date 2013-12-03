using Fizbin.Kinect.Gestures.Segments;
using Microsoft.Kinect;
using Microsoft.Kinect.Toolkit;
using Microsoft.Samples.Kinect.WpfViewers;
using Microsoft.Speech.AudioFormat;
using Microsoft.Speech.Recognition;
using Newtonsoft.Json;
using SharpVoice;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Timers;
using System.Windows;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Media;


namespace Fizbin.Kinect.Gestures.Demo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        private readonly KinectSensorChooser sensorChooser = new KinectSensorChooser();

        private Skeleton[] skeletons = new Skeleton[0];

        private bool ARDUINO_IN = false;             // flag to enable SendCommandToArduino

        // CONSTANTS
        private const int TV_ON = 118;
        private const int TV_OFF = 117;
        private const int TV_MUTE = 67;
        private const int CHANNEL_UP = 119;
        private const int CHANNEL_DOWN = 120;
        private const int VOLUME_UP = 121;
        private const int VOLUME_DOWN = 122;
        private const int APPLIANCE_OFF = 61;
        private const int APPLIANCE_ON = 66;
        private const int LIGHT_OFF = 97;
        private const int LIGHT_ON = 106;
        private const int CURTAIN_OFF = 107;
        private const int CURTAIN_ON = 116;
        private const int TV_CHANNEL_FOOD_NETWORK = 123;
        

        // Variable intensity values
        private int light = LIGHT_OFF;              // [97 - 106]
        private int curtain = CURTAIN_OFF;          // [107 - 116]
        private int appliance = APPLIANCE_OFF;      // [61 - 66]

        // Flags to check for device status
        private bool tvIsOn = false;

        // Current Appliance Control Mode
        private const string LIGHT_MODE = "LIGHTS MODE";
        private const string GENERAL_MODE = "GENERAL MODE";
        private const string TV_MODE = "TELEVISION MODE";
        private const string APPLIANCE_MODE = "APPLIANCE MODE";
        private string MODE = LIGHT_MODE;

        
        Timer _clearTimer;
        SerialPort serialPort;


        // skeleton gesture recognizer
        private GestureController gestureController;

        public MainWindow()
        {
            Console.WriteLine("MainWindow()");
            DataContext = this;

            InitializeComponent();

            // initialize the Kinect sensor manager
            KinectSensorManager = new KinectSensorManager();
            KinectSensorManager.KinectSensorChanged += this.KinectSensorChanged;

            // locate an available sensor
            sensorChooser.Start();

            // bind chooser's sensor value to the local sensor manager
            var kinectSensorBinding = new Binding("Kinect") { Source = this.sensorChooser };
            BindingOperations.SetBinding(this.KinectSensorManager, KinectSensorManager.KinectSensorProperty, kinectSensorBinding);

			// add timer for clearing last detected gesture
            _clearTimer = new Timer(2000);
            _clearTimer.Elapsed += new ElapsedEventHandler(clearTimer_Elapsed);

            // add SerialPort for sending messages to Arduino
            serialPort = new SerialPort("COM4", 9600);
        }

        #region Kinect Discovery & Setup

        private void KinectSensorChanged(object sender, KinectSensorManagerEventArgs<KinectSensor> args)
        {
            if (null != args.OldValue)
                UninitializeKinectServices(args.OldValue);

            if (null != args.NewValue)
                InitializeKinectServices(KinectSensorManager, args.NewValue);
        }

        /// <summary>
        /// Kinect enabled apps should customize which Kinect services it initializes here.
        /// </summary>
        /// <param name="kinectSensorManager"></param>
        /// <param name="sensor"></param>
        private void InitializeKinectServices(KinectSensorManager kinectSensorManager, KinectSensor sensor)
        {
            // Application should enable all streams first.

            // configure the color stream
            kinectSensorManager.ColorFormat = ColorImageFormat.RgbResolution640x480Fps30;
            kinectSensorManager.ColorStreamEnabled = true;

            // configure the depth stream
            kinectSensorManager.DepthStreamEnabled = true;

            kinectSensorManager.TransformSmoothParameters =
                new TransformSmoothParameters
                {
                    Smoothing = 0.5f,
                    Correction = 0.5f,
                    Prediction = 0.5f,
                    JitterRadius = 0.05f,
                    MaxDeviationRadius = 0.04f
                };

            // configure the skeleton stream
            sensor.SkeletonFrameReady += OnSkeletonFrameReady;
            kinectSensorManager.SkeletonStreamEnabled = true;

            kinectSensorManager.KinectSensorEnabled = true;

            if (!kinectSensorManager.KinectSensorAppConflict)
            {
                // initialize the gesture recognizer
                gestureController = new GestureController();
                gestureController.GestureRecognized += OnGestureRecognized;

                // register the gestures for this demo
                RegisterGestures();
            }
        }

        /// <summary>
        /// Kinect enabled apps should uninitialize all Kinect services that were initialized in InitializeKinectServices() here.
        /// </summary>
        /// <param name="sensor"></param>
        private void UninitializeKinectServices(KinectSensor sensor)
        {
            // unregister the event handlers
            sensor.SkeletonFrameReady -= OnSkeletonFrameReady;
            gestureController.GestureRecognized -= OnGestureRecognized;
        }

        #endregion Kinect Discovery & Setup

        /// <summary>
        /// Helper function to register all available 
        /// </summary>
        private void RegisterGestures()
        {
            // define the gestures for the demo
            Console.WriteLine("RegisterGestures()");
            IRelativeGestureSegment[] joinedhandsSegments = new IRelativeGestureSegment[20];
            JoinedHandsSegment1 joinedhandsSegment = new JoinedHandsSegment1();
            for (int i = 0; i < 20; i++)
            {
                // gesture consists of the same thing 10 times 
                joinedhandsSegments[i] = joinedhandsSegment;
            }
            gestureController.AddGesture("JoinedHands", joinedhandsSegments);

            IRelativeGestureSegment[] menuSegments = new IRelativeGestureSegment[20];
            MenuSegment1 menuSegment = new MenuSegment1();
            for (int i = 0; i < 20; i++)
            {
                // gesture consists of the same thing 20 times 
                menuSegments[i] = menuSegment;
            }
            gestureController.AddGesture("Menu", menuSegments);

            IRelativeGestureSegment[] swipeleftSegments = new IRelativeGestureSegment[3];
            swipeleftSegments[0] = new SwipeLeftSegment1();
            swipeleftSegments[1] = new SwipeLeftSegment2();
            swipeleftSegments[2] = new SwipeLeftSegment3();
            gestureController.AddGesture("SwipeLeft", swipeleftSegments);

            IRelativeGestureSegment[] swiperightSegments = new IRelativeGestureSegment[3];
            swiperightSegments[0] = new SwipeRightSegment1();
            swiperightSegments[1] = new SwipeRightSegment2();
            swiperightSegments[2] = new SwipeRightSegment3();
            gestureController.AddGesture("SwipeRight", swiperightSegments);

            IRelativeGestureSegment[] waveRightSegments = new IRelativeGestureSegment[6];
            WaveRightSegment1 waveRightSegment1 = new WaveRightSegment1();
            WaveRightSegment2 waveRightSegment2 = new WaveRightSegment2();
            waveRightSegments[0] = waveRightSegment1;
            waveRightSegments[1] = waveRightSegment2;
            waveRightSegments[2] = waveRightSegment1;
            waveRightSegments[3] = waveRightSegment2;
            waveRightSegments[4] = waveRightSegment1;
            waveRightSegments[5] = waveRightSegment2;
            gestureController.AddGesture("WaveRight", waveRightSegments);

            IRelativeGestureSegment[] waveLeftSegments = new IRelativeGestureSegment[6];
            WaveLeftSegment1 waveLeftSegment1 = new WaveLeftSegment1();
            WaveLeftSegment2 waveLeftSegment2 = new WaveLeftSegment2();
            waveLeftSegments[0] = waveLeftSegment1;
            waveLeftSegments[1] = waveLeftSegment2;
            waveLeftSegments[2] = waveLeftSegment1;
            waveLeftSegments[3] = waveLeftSegment2;
            waveLeftSegments[4] = waveLeftSegment1;
            waveLeftSegments[5] = waveLeftSegment2;
            gestureController.AddGesture("WaveLeft", waveLeftSegments);

            IRelativeGestureSegment[] zoomInSegments = new IRelativeGestureSegment[3];
            zoomInSegments[0] = new ZoomSegment1();
            zoomInSegments[1] = new ZoomSegment2();
            zoomInSegments[2] = new ZoomSegment3();
            gestureController.AddGesture("ZoomIn", zoomInSegments);

            IRelativeGestureSegment[] zoomOutSegments = new IRelativeGestureSegment[3];
            zoomOutSegments[0] = new ZoomSegment3();
            zoomOutSegments[1] = new ZoomSegment2();
            zoomOutSegments[2] = new ZoomSegment1();
            gestureController.AddGesture("ZoomOut", zoomOutSegments);
            
            IRelativeGestureSegment[] swipeUpSegments = new IRelativeGestureSegment[3];
            swipeUpSegments[0] = new SwipeUpSegment1();
            swipeUpSegments[1] = new SwipeUpSegment2();
            swipeUpSegments[2] = new SwipeUpSegment3();
            gestureController.AddGesture("SwipeUp", swipeUpSegments);

            IRelativeGestureSegment[] swipeDownSegments = new IRelativeGestureSegment[3];
            swipeDownSegments[0] = new SwipeDownSegment1();
            swipeDownSegments[1] = new SwipeDownSegment2();
            swipeDownSegments[2] = new SwipeDownSegment3();
            gestureController.AddGesture("SwipeDown", swipeDownSegments);
            
            IRelativeGestureSegment[] raisetheRoofSegments = new IRelativeGestureSegment[4];
            raisetheRoofSegments[0] = new RaiseTheRoofSegment1();
            raisetheRoofSegments[1] = new RaiseTheRoofSegment2();
            raisetheRoofSegments[2] = new RaiseTheRoofSegment1();
            raisetheRoofSegments[3] = new RaiseTheRoofSegment2();
            gestureController.AddGesture("RaiseTheRoof", raisetheRoofSegments);

        }

        #region Properties

        public static readonly DependencyProperty KinectSensorManagerProperty =
            DependencyProperty.Register(
                "KinectSensorManager",
                typeof(KinectSensorManager),
                typeof(MainWindow),
                new PropertyMetadata(null));

        public KinectSensorManager KinectSensorManager
        {
            get { return (KinectSensorManager)GetValue(KinectSensorManagerProperty); }
            set { SetValue(KinectSensorManagerProperty, value); }
        }

        /// <summary>
        /// Gets or sets the last recognized gesture.
        /// </summary>
        private string _gesture;
        public String Gesture
        {
            get { return _gesture; }

            private set
            {
                if (_gesture == value)
                    return;

                _gesture = value;

                if (this.PropertyChanged != null)
                    PropertyChanged(this, new PropertyChangedEventArgs("Gesture"));
            }
        }

        #endregion Properties

        #region Events

        /// <summary>
        /// Event implementing INotifyPropertyChanged interface.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        #endregion Events

        #region Event Handlers

        private void OnRaiseTheRoof()
        {
            System.Media.SoundPlayer player = new System.Media.SoundPlayer(@"C:\Users\Derek\Documents\GitHub\cse-118-yolo-secret-ninja\Fizbin.Kinect.Gestures-master\Fizbin.Kinect.Gestures-master\Fizbin.Kinect.Gestures.Demo\Pikachu.wav");
            player.Play();
            CallSomeone("It's PARTY TIME!!!");
        }

        private void SleepTime()
        {
            Console.WriteLine("Sleep Time enabled");
            if (ARDUINO_IN)
            {
                light = LIGHT_OFF;
                SendCommandToArduino(LIGHT_OFF);
                SendCommandToArduino(CURTAIN_OFF);
                if (tvIsOn)
                {
                    SendCommandToArduino(TV_OFF);
                    tvIsOn = false;
                }
                SendCommandToArduino(APPLIANCE_OFF);   
            }
        }


        private void CallSomeone(string msg)
        {
            Voice v = new Voice("koaswift@gmail.com", "cse118team8");
            v.Call("+19255481182", "koaswift@gmail.com");               // Call from Google Voice Account -> Gmail account (Must have window open)
            // v.SendSMS("+19255481182", msg + " - Kirsten's Phone");
            v.SendSMS("+17027684490", msg + " - Derek's Phone");

        }

        private void SendCommandToArduino(int msg)
        {
            if (!serialPort.IsOpen)
            serialPort.Open();
            serialPort.Write(""+(char)msg);   
        }

        /// <summary>
        ///
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e">Gesture event arguments.</param>


        private void OnGestureRecognized(object sender, GestureEventArgs e)
        {
            switch (e.GestureName)
            {
                case "RaiseTheRoof":
                    Gesture = "Raise The Roof!";
                    this.OnRaiseTheRoof();
                    break;
                case "Menu":
                    Gesture = "Menu";
                    break;
                case "WaveRight":
                    Gesture = "Wave Right";
                    break;
                case "WaveLeft":
                    Gesture = "Wave Left";
                    break;
                case "JoinedHands":
                    Gesture = "Joined Hands";
                    this.SleepTime();
                    break;
                case "SwipeLeft":
                    Gesture = "Swipe Left";
                    if (MODE.Equals(TV_MODE))
                    {
                        TurnTvVolumeUp();
                    }
                    else if (MODE.Equals(LIGHT_MODE))
                    {
                        TurnLightUp();
                    }
                    break;
                case "SwipeRight":
                    Gesture = "Swipe Right";
                    if (MODE.Equals(TV_MODE))
                    {
                        TurnTvVolumeDown();
                    }
                    else if (MODE.Equals(LIGHT_MODE))
                    {
                        TurnLightDown();
                    }
                    break;
                case "SwipeUp":
                    Gesture = "Swipe Up";
                    if (MODE.Equals(TV_MODE))
                    {
                        TurnTvChannelUp();
                    }
                    else if (MODE.Equals(APPLIANCE_MODE))
                    {
                        Console.WriteLine("APPLIANCE UP");
                        if (appliance < APPLIANCE_ON) appliance += 1;
                        if (ARDUINO_IN) this.SendCommandToArduino(appliance);
                    }
                    break;
                case "SwipeDown":
                    Gesture = "Swipe Down";
                    if (MODE.Equals(TV_MODE))
                    {
                        TurnTvChannelDown();
                    }
                    else if (MODE.Equals(APPLIANCE_MODE))
                    {
                        Console.WriteLine("APPLIANCE DOWN");
                        if (appliance > APPLIANCE_OFF) appliance -= 1;
                        if (ARDUINO_IN) this.SendCommandToArduino(appliance);
                    }
                    break;
                case "ZoomIn":
                    Gesture = "Zoom In";
                    if (MODE.Equals(TV_MODE))
                    {
                        TurnTvOn();
                    }
                    else if (MODE.Equals(LIGHT_MODE))
                    {
                        TurnLightOn();
                    }
                    break;
                case "ZoomOut":
                    Gesture = "Zoom Out";
                    if (MODE.Equals(TV_MODE))
                    {
                        TurnTvOff();
                    }
                    else if (MODE.Equals(LIGHT_MODE))
                    {
                        TurnLightOff();
                    }
                    break;
                default:
                    Gesture = "None detected";
                    break;
            }

            //Console.WriteLine("HALLO " + Gesture);
            Console.WriteLine(MODE);
            _clearTimer.Start();
        }

        private void TurnLightDown()
        {
            Console.WriteLine("LIGHT DECREASE");
            if (light > LIGHT_OFF) light -= 1;
            if (ARDUINO_IN) this.SendCommandToArduino(light);
        }

        private void TurnLightUp()
        {
            Console.WriteLine("LIGHT INCREASE");
            if (light < LIGHT_ON) light += 1;
            if (ARDUINO_IN) this.SendCommandToArduino(light);
        }

        private void TurnTvChannelDown()
        {
            SendTvCommand("TV CHANNEL DOWN", CHANNEL_DOWN);
        }

        private void TurnTvChannelUp()
        {
            SendTvCommand("TV CHANNEL UP", CHANNEL_UP);
        }

        private void ChangeTvChannel()
        {
            SendTvCommand("TV CHANNEL CHANGE", TV_CHANNEL_FOOD_NETWORK);
        }

        private void MuteTv()
        {
            SendTvCommand("MUTE TV", TV_MUTE);
        }


        private void TurnLightOn()
        {
            Console.WriteLine("LIGHT ON");
            if (ARDUINO_IN) this.SendCommandToArduino(LIGHT_ON);
            light = LIGHT_ON;
        }

        private void TurnLightOff()
        {
            Console.WriteLine("LIGHT OFF");
            if (ARDUINO_IN) this.SendCommandToArduino(LIGHT_OFF);
            light = LIGHT_OFF;
        }

        private void DimLight(int level)
        {
            Console.WriteLine("LIGHT DIM " + level);
            int light_state = LIGHT_OFF + (level % 6);
            light = light_state;
            if (ARDUINO_IN) this.SendCommandToArduino(light);
        }

        private void TurnTvVolumeDown()
        {
            SendTvCommand("TV VOLUME DOWN", VOLUME_DOWN);
        }

        private void TurnTvVolumeUp()
        {
            SendTvCommand("TV VOLUME UP", VOLUME_UP);
        }

        private void SendTvCommand(string cmd, int IR_Signal)
        {
            if (tvIsOn)
            {
                Console.WriteLine(cmd);
                if (ARDUINO_IN) this.SendCommandToArduino(IR_Signal);
            }
        }

        private void TurnTvOff()
        {
            SendTvCommand("TV OFF", TV_OFF);
            tvIsOn = false;
        }

        private void TurnTvOn()
        {
            if (!tvIsOn)
            {
                tvIsOn = true;
                SendTvCommand("TV ON", TV_ON);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnSkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            using (SkeletonFrame frame = e.OpenSkeletonFrame())//
            {
                if (frame == null)
                    return;

                // resize the skeletons array if needed
                if (skeletons.Length != frame.SkeletonArrayLength)
                    skeletons = new Skeleton[frame.SkeletonArrayLength];

                // get the skeleton data
                frame.CopySkeletonDataTo(skeletons);

                foreach (var skeleton in skeletons)
                {
                    // skip the skeleton if it is not being tracked
                    if (skeleton.TrackingState != SkeletonTrackingState.Tracked)
                        continue;

                    // update the gesture controller
                    gestureController.UpdateAllGestures(skeleton);
                }
            }
        }

        /// <summary>
        /// Clear text after some time
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void clearTimer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Gesture = "";
            _clearTimer.Stop();
        }

        #endregion Event Handlers

    


    ///////////////////////// SPEECH CODE /////////////////////////////////////


        /// <summary>
        /// Resource key for medium-gray-colored brush.
        /// </summary>
        private const string MediumGreyBrushKey = "MediumGreyBrush";

        /// <summary>
        /// Map between each direction and the direction immediately to its left.
        /// </summary>
        private static readonly Dictionary<LightState, LightState> OppositeState = new Dictionary<LightState, LightState>
            {
                { LightState.On, LightState.Off },
                { LightState.Off, LightState.On }
            };

        /// <summary>
        /// Active Kinect sensor.
        /// </summary>
        private KinectSensor sensor;

        /// <summary>
        /// Speech recognition engine using audio data from Kinect.
        /// </summary>
        private SpeechRecognitionEngine speechEngine;

        /// <summary>
        /// Current direction where turtle is facing.
        /// </summary>
        private LightState currentLightState = LightState.Off;

        /// <summary>
        /// List of all UI span elements used to select recognized text.
        /// </summary>
        private List<Span> recognitionSpans;

        /// <summary>
        /// Enumeration of directions in which turtle may be facing.
        /// </summary>
        private enum LightState
        {
            On,
            Off,
        }
        
        /// <summary>
        /// Gets the metadata for the speech recognizer (acoustic model) most suitable to
        /// process audio from Kinect device.
        /// </summary>
        /// <returns>
        /// RecognizerInfo if found, <code>null</code> otherwise.
        /// </returns>
        private static RecognizerInfo GetKinectRecognizer()
        {
            foreach (RecognizerInfo recognizer in SpeechRecognitionEngine.InstalledRecognizers())
            {
                string value;
                recognizer.AdditionalInfo.TryGetValue("Kinect", out value);
                if ("True".Equals(value, StringComparison.OrdinalIgnoreCase) && "en-US".Equals(recognizer.Culture.Name, StringComparison.OrdinalIgnoreCase))
                {
                    return recognizer;
                }
            }
            
            return null;
        }

        /// <summary>
        /// Execute initialization tasks.
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void WindowLoaded(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("WindowLoaded");
            // Look through all sensors and start the first connected one.
            // This requires that a Kinect is connected at the time of app startup.
            // To make your app robust against plug/unplug, 
            // it is recommended to use KinectSensorChooser provided in Microsoft.Kinect.Toolkit (See components in Toolkit Browser).
            foreach (var potentialSensor in KinectSensor.KinectSensors)
            {
                if (potentialSensor.Status == KinectStatus.Connected)
                {
                    this.sensor = potentialSensor;
                    break;
                }
            }

            if (null != this.sensor)
            {
                try
                {
                    // Start the sensor!
                    this.sensor.Start();
                }
                catch (IOException)
                {
                    // Some other application is streaming from the same Kinect sensor
                    this.sensor = null;
                }
            }

            if (null == this.sensor)
            {
                //this.statusBarText.Text = Properties.Resources.NoKinectReady;
                return;
            }

            RecognizerInfo ri = GetKinectRecognizer();

            if (null != ri)
            {
                //recognitionSpans = new List<Span> { onSpan, offSpan, oppositeSpan };

                this.speechEngine = new SpeechRecognitionEngine(ri.Id);

                /****************************************************************
                * 
                * Use this code to create grammar programmatically rather than from
                * a grammar file.
                * 
                * var directions = new Choices();
                * directions.Add(new SemanticResultValue("forward", "FORWARD"));
                * directions.Add(new SemanticResultValue("forwards", "FORWARD"));
                * directions.Add(new SemanticResultValue("straight", "FORWARD"));
                * directions.Add(new SemanticResultValue("backward", "BACKWARD"));
                * directions.Add(new SemanticResultValue("backwards", "BACKWARD"));
                * directions.Add(new SemanticResultValue("back", "BACKWARD"));
                * directions.Add(new SemanticResultValue("turn left", "LEFT"));
                * directions.Add(new SemanticResultValue("turn right", "RIGHT"));
                *
                * var gb = new GrammarBuilder { Culture = ri.Culture };
                * gb.Append(directions);
                *
                * var g = new Grammar(gb);
                * 
                ****************************************************************/
                string str = System.IO.File.ReadAllText(@"C:\Users\Patrick\Documents\GitHub\cse-118-yolo-secret-ninja\Fizbin.Kinect.Gestures-master\Fizbin.Kinect.Gestures-master\Fizbin.Kinect.Gestures.Demo\SpeechGrammar.xml"); //Properties.Resources.SpeechGrammar;
                Console.WriteLine("speech grammar " + str);
                byte[] grammarz = Encoding.ASCII.GetBytes(str);
                int i = 023 + 2;
                Console.WriteLine("hi");
                // Create a grammar from grammar definition XML file.
                using (var memoryStream = new MemoryStream(grammarz))
                {
                    var g = new Grammar(memoryStream);
                    speechEngine.LoadGrammar(g);
                }

                speechEngine.SpeechRecognized += SpeechRecognized;
                speechEngine.SpeechRecognitionRejected += SpeechRejected;

                // For long recognition sessions (a few hours or more), it may be beneficial to turn off adaptation of the acoustic model. 
                // This will prevent recognition accuracy from degrading over time.
                ////speechEngine.UpdateRecognizerSetting("AdaptationOn", 0);

                speechEngine.SetInputToAudioStream(
                    sensor.AudioSource.Start(), new SpeechAudioFormatInfo(EncodingFormat.Pcm, 16000, 16, 1, 32000, 2, null));
                speechEngine.RecognizeAsync(RecognizeMode.Multiple);
            }
            else
            {
                //this.statusBarText.Text = Properties.Resources.NoSpeechRecognizer;
            }
        }

        /// <summary>
        /// Execute uninitialization tasks.
        /// </summary>
        /// <param name="sender">object sending the event.</param>
        /// <param name="e">event arguments.</param>
        private void WindowClosing(object sender, CancelEventArgs e)
        {
            if (null != this.sensor)
            {
                this.sensor.AudioSource.Stop();

                this.sensor.Stop();
                this.sensor = null;
            }

            if (null != this.speechEngine)
            {
                this.speechEngine.SpeechRecognized -= SpeechRecognized;
                this.speechEngine.SpeechRecognitionRejected -= SpeechRejected;
                this.speechEngine.RecognizeAsyncStop();
            }
        }

        /// <summary>
        /// Remove any highlighting from recognition instructions.
        /// </summary>
        private void ClearRecognitionHighlights()
        {
       /*     foreach (Span span in recognitionSpans)
            {
                span.Foreground = (Brush)this.Resources[MediumGreyBrushKey];
                span.FontWeight = FontWeights.Normal;
            }*/
        }

        /// <summary>
        /// Handler for recognized speech events.
        /// </summary>
        /// <param name="sender">object sending the event.</param>
        /// <param name="e">event arguments.</param>
        private void SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            // Speech utterance confidence below which we treat speech as if it hadn't been heard
            const double ConfidenceThreshold = 0.5;
            Console.WriteLine("speech recognized");

            ClearRecognitionHighlights();

            if (e.Result.Confidence >= ConfidenceThreshold)
            {
                //Console.WriteLine(e.Result.Text.ToString());
                Console.WriteLine(e.Result.Semantics["action"].Value.ToString());
                MODE = e.Result.Semantics["action"].Value.ToString();
                switch (e.Result.Semantics["action"].Value.ToString())
                {
                    case "HELP":
                        CallSomeone(e.Result.Text.ToString());
                        break;
                    case "LIGHTS ON":
                        TurnLightOn();
                        break;
                    case "LIGHTS OFF":
                        TurnLightOff();
                        break;
                    case "LIGHTS DIM":
                        DimLight(int.Parse(e.Result.Semantics["level"].Value.ToString()));
                        break;
                    case "CURTAINS OPEN":
                        break;
                    case "CURTAINS CLOSE":
                        break;
                    case "TELEVISION ON":
                        TurnTvOn();
                        break;
                    case "TELEVISION OFF":
                        TurnTvOff();
                        break;
                    case "TELEVISION CHANNEL UP":
                        TurnTvChannelUp();
                        break;
                    case "TELEVISION CHANNEL DOWN":
                        TurnTvChannelDown();
                        break;
                    case "TELEVISION VOLUME UP":
                        TurnTvVolumeUp();
                        break;
                    case "TELEVISION VOLUME DOWN":
                        TurnTvVolumeDown();
                        break;
                    case "TELEVISION MUTE":
                        MuteTv();
                        break;
                    case "TELEVISION CHANNEL FOOD NETWORK":
                        ChangeTvChannel();
                        break;


                }
            }
        }

        /// <summary>
        /// Handler for rejected speech events.
        /// </summary>
        /// <param name="sender">object sending the event.</param>
        /// <param name="e">event arguments.</param>
        private void SpeechRejected(object sender, SpeechRecognitionRejectedEventArgs e)
        {
            ClearRecognitionHighlights();
        }
    }
}

