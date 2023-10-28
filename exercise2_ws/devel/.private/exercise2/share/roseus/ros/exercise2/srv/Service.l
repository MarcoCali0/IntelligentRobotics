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





(defclass exercise2::ServiceRequest
  :super ros::object
  :slots (_station_ID ))

(defmethod exercise2::ServiceRequest
  (:init
   (&key
    ((:station_ID __station_ID) 0)
    )
   (send-super :init)
   (setq _station_ID (round __station_ID))
   self)
  (:station_ID
   (&optional __station_ID)
   (if __station_ID (setq _station_ID __station_ID)) _station_ID)
  (:serialization-length
   ()
   (+
    ;; int16 _station_ID
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _station_ID
       (write-word _station_ID s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
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
    ((:header __header) "")
    ((:message __message) (instance exercise2::Message :init))
    )
   (send-super :init)
   (setq _header (string __header))
   (setq _message __message)
   self)
  (:header
   (&optional __header)
   (if __header (setq _header __header)) _header)
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
    ;; string _header
    4 (length _header)
    ;; exercise2/Message _message
    (send _message :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _header
       (write-long (length _header) s) (princ _header s)
     ;; exercise2/Message _message
       (send _message :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _header
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _header (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; exercise2/Message _message
     (send _message :deserialize buf ptr-) (incf ptr- (send _message :serialization-length))
   ;;
   self)
  )

(defclass exercise2::Service
  :super ros::object
  :slots ())

(setf (get exercise2::Service :md5sum-) "21bd264f074ea134fbba0e8079d12124")
(setf (get exercise2::Service :datatype-) "exercise2/Service")
(setf (get exercise2::Service :request) exercise2::ServiceRequest)
(setf (get exercise2::Service :response) exercise2::ServiceResponse)

(defmethod exercise2::ServiceRequest
  (:response () (instance exercise2::ServiceResponse :init)))

(setf (get exercise2::ServiceRequest :md5sum-) "21bd264f074ea134fbba0e8079d12124")
(setf (get exercise2::ServiceRequest :datatype-) "exercise2/ServiceRequest")
(setf (get exercise2::ServiceRequest :definition-)
      "# request
# string header
int16 station_ID
---
# response
string header 
Message message

================================================================================
MSG: exercise2/Message
# name of the room
string room_name

# ID of the room
int8 room_ID

# level of charge of the robot battery
")

(setf (get exercise2::ServiceResponse :md5sum-) "21bd264f074ea134fbba0e8079d12124")
(setf (get exercise2::ServiceResponse :datatype-) "exercise2/ServiceResponse")
(setf (get exercise2::ServiceResponse :definition-)
      "# request
# string header
int16 station_ID
---
# response
string header 
Message message

================================================================================
MSG: exercise2/Message
# name of the room
string room_name

# ID of the room
int8 room_ID

# level of charge of the robot battery
")



(provide :exercise2/Service "21bd264f074ea134fbba0e8079d12124")


