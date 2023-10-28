;; Auto-generated. Do not edit!


(when (boundp 'exercise2::Message)
  (if (not (find-package "EXERCISE2"))
    (make-package "EXERCISE2"))
  (shadow 'Message (find-package "EXERCISE2")))
(unless (find-package "EXERCISE2::MESSAGE")
  (make-package "EXERCISE2::MESSAGE"))

(in-package "ROS")
;;//! \htmlinclude Message.msg.html


(defclass exercise2::Message
  :super ros::object
  :slots (_room_name _room_ID _charge_level ))

(defmethod exercise2::Message
  (:init
   (&key
    ((:room_name __room_name) "")
    ((:room_ID __room_ID) 0)
    ((:charge_level __charge_level) 0)
    )
   (send-super :init)
   (setq _room_name (string __room_name))
   (setq _room_ID (round __room_ID))
   (setq _charge_level (round __charge_level))
   self)
  (:room_name
   (&optional __room_name)
   (if __room_name (setq _room_name __room_name)) _room_name)
  (:room_ID
   (&optional __room_ID)
   (if __room_ID (setq _room_ID __room_ID)) _room_ID)
  (:charge_level
   (&optional __charge_level)
   (if __charge_level (setq _charge_level __charge_level)) _charge_level)
  (:serialization-length
   ()
   (+
    ;; string _room_name
    4 (length _room_name)
    ;; int8 _room_ID
    1
    ;; int8 _charge_level
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _room_name
       (write-long (length _room_name) s) (princ _room_name s)
     ;; int8 _room_ID
       (write-byte _room_ID s)
     ;; int8 _charge_level
       (write-byte _charge_level s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _room_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _room_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int8 _room_ID
     (setq _room_ID (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _room_ID 127) (setq _room_ID (- _room_ID 256)))
   ;; int8 _charge_level
     (setq _charge_level (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _charge_level 127) (setq _charge_level (- _charge_level 256)))
   ;;
   self)
  )

(setf (get exercise2::Message :md5sum-) "7c2be1ef585767ad1a0db978f95b4587")
(setf (get exercise2::Message :datatype-) "exercise2/Message")
(setf (get exercise2::Message :definition-)
      "# name of the room
string room_name

# ID of the room
int8 room_ID

# level of charge of the robot battery
int8 charge_level
")



(provide :exercise2/Message "7c2be1ef585767ad1a0db978f95b4587")


