// Auto-generated. Do not edit!

// (in-package exercise1.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Message {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.room_name = null;
      this.room_ID = null;
      this.charge_level = null;
    }
    else {
      if (initObj.hasOwnProperty('room_name')) {
        this.room_name = initObj.room_name
      }
      else {
        this.room_name = '';
      }
      if (initObj.hasOwnProperty('room_ID')) {
        this.room_ID = initObj.room_ID
      }
      else {
        this.room_ID = 0;
      }
      if (initObj.hasOwnProperty('charge_level')) {
        this.charge_level = initObj.charge_level
      }
      else {
        this.charge_level = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Message
    // Serialize message field [room_name]
    bufferOffset = _serializer.string(obj.room_name, buffer, bufferOffset);
    // Serialize message field [room_ID]
    bufferOffset = _serializer.int8(obj.room_ID, buffer, bufferOffset);
    // Serialize message field [charge_level]
    bufferOffset = _serializer.int8(obj.charge_level, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Message
    let len;
    let data = new Message(null);
    // Deserialize message field [room_name]
    data.room_name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [room_ID]
    data.room_ID = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [charge_level]
    data.charge_level = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.room_name);
    return length + 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'exercise1/Message';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7c2be1ef585767ad1a0db978f95b4587';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Message(null);
    if (msg.room_name !== undefined) {
      resolved.room_name = msg.room_name;
    }
    else {
      resolved.room_name = ''
    }

    if (msg.room_ID !== undefined) {
      resolved.room_ID = msg.room_ID;
    }
    else {
      resolved.room_ID = 0
    }

    if (msg.charge_level !== undefined) {
      resolved.charge_level = msg.charge_level;
    }
    else {
      resolved.charge_level = 0
    }

    return resolved;
    }
};

module.exports = Message;
