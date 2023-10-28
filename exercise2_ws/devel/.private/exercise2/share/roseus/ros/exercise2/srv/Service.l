;; Auto-generated. Do not edit!


(when (boundp 'exercise2::Service)
  (if (not (find-package "EXERCISE2"))
    (make-package "EXERCISE2"))
  (shadow 'Service (find-package "EXERCISE2")))
(unless (find-package "EXERCISE2::SERVICE")
  (make-package "EXERCISE2::SERVICE"))
(unless (find-package "EXERCISE2::SERVICEREQUEST")
  (make-package "EXERCISE2::SERVICEREQUEST"))
(unless (find-package "EXERCISE2::SERVICERESPONSE")
  (make-package "EXERCISE2::SERVICERESPONSE"))

(in-package "ROS")

(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass exercise2::ServiceRequest
  :super ros::object
  :slots (_header _station_ID ))

(defmethod exercise2::ServiceRequest
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:station_ID __station_ID) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _station_ID (round __station_ID))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:station_ID
   (&optional __station_ID)
   (if __station_ID (setq _station_ID __station_ID)) _station_ID)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int16 _station_ID
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int16 _station_ID
       (write-word _station_ID s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int16 _station_ID
     (setq _station_ID (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(defclass exercise2::ServiceResponse
  :super ros::object
  :slots (_header _message ))

(defmethod exercise2::ServiceResponse
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:message __message) (instance exercise2::Message :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _message __message)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:message
   (&rest __message)
   (if (keywordp (car __message))
       (send* _message __message)
     (progn
       (if __message (setq _message (car __message)))
       _message)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; exercise2/Message _message
    (send _message :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; exercise2/Message _message
       (send _message :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; exercise2/Message _message
     (send _message :deserialize buf ptr-) (incf ptr- (send _message :serialization-length))
   ;;
   self)
  )

(defclass exercise2::Service
  :super ros::object
  :slots ())

(setf (get exercise2::Service :md5sum-) "c2fa96eb2bd06c7aa128b61b7f5a3487")
(setf (get exercise2::Service :datatype-) "exercise2/Service")
(setf (get exercise2::Service :request) exercise2::ServiceRequest)
(setf (get exercise2::Service :response) exercise2::ServiceResponse)

(defmethod exercise2::ServiceRequest
  (:response () (instance exercise2::ServiceResponse :init)))

(setf (get exercise2::ServiceRequest :md5sum-) "c2fa96eb2bd06c7aa128b61b7f5a3487")
(setf (get exercise2::ServiceRequest :datatype-) "exercise2/ServiceRequest")
(setf (get exercise2::ServiceRequest :definition-)
      "# request
std_msgs/Header header
int16 station_ID

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
---
# response
std_msgs/Header header
Message message

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: exercise2/Message
# name of the room
string room_name

# ID of the room
int8 room_ID

# level of charge of the robot battery
")

(setf (get exercise2::ServiceResponse :md5sum-) "c2fa96eb2bd06c7aa128b61b7f5a3487")
(setf (get exercise2::ServiceResponse :datatype-) "exercise2/ServiceResponse")
(setf (get exercise2::ServiceResponse :definition-)
      "# request
std_msgs/Header header
int16 station_ID

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id
---
# response
std_msgs/Header header
Message message

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: exercise2/Message
# name of the room
string room_name

# ID of the room
int8 room_ID

# level of charge of the robot battery
")



(provide :exercise2/Service "c2fa96eb2bd06c7aa128b61b7f5a3487")


