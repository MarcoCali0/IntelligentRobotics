// Auto-generated. Do not edit!

// (in-package exercise2.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let Message = require('../msg/Message.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class ServiceRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.station_ID = null;
    }
    else {
      if (initObj.hasOwnProperty('station_ID')) {
        this.station_ID = initObj.station_ID
      }
      else {
        this.station_ID = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ServiceRequest
    // Serialize message field [station_ID]
    bufferOffset = _serializer.int16(obj.station_ID, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ServiceRequest
    let len;
    let data = new ServiceRequest(null);
    // Deserialize message field [station_ID]
    data.station_ID = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a service object
    return 'exercise2/ServiceRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'aedbf9b210b5af3c248bf527a8382076';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # request
    # std_msgs/Header header
    int16 station_ID
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ServiceRequest(null);
    if (msg.station_ID !== undefined) {
      resolved.station_ID = msg.station_ID;
    }
    else {
      resolved.station_ID = 0
    }

    return resolved;
    }
};

class ServiceResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.message = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('message')) {
        this.message = initObj.message
      }
      else {
        this.message = new Message();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ServiceResponse
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [message]
    bufferOffset = Message.serialize(obj.message, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ServiceResponse
    let len;
    let data = new ServiceResponse(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [message]
    data.message = Message.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += Message.getMessageSize(object.message);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'exercise2/ServiceResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '10cacc6f68c7bbd99eb534415926e511';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    int8 charge_level
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ServiceResponse(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.message !== undefined) {
      resolved.message = Message.Resolve(msg.message)
    }
    else {
      resolved.message = new Message()
    }

    return resolved;
    }
};

module.exports = {
  Request: ServiceRequest,
  Response: ServiceResponse,
  md5sum() { return '9671e58bec85efbba1923ae558a87802'; },
  datatype() { return 'exercise2/Service'; }
};
