// This file is generated by rust-protobuf 3.2.0. Do not edit
// .proto file is parsed by protoc 3.21.6
// @generated

// https://github.com/rust-lang/rust-clippy/issues/702
#![allow(unknown_lints)]
#![allow(clippy::all)]

#![allow(unused_attributes)]
#![cfg_attr(rustfmt, rustfmt::skip)]

#![allow(box_pointers)]
#![allow(dead_code)]
#![allow(missing_docs)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(trivial_casts)]
#![allow(unused_results)]
#![allow(unused_mut)]

//! Generated file from `protos/upload.proto`

/// Generated files are compatible only with the same version
/// of protobuf runtime.
const _PROTOBUF_VERSION_CHECK: () = ::protobuf::VERSION_3_2_0;

#[derive(PartialEq,Clone,Default,Debug)]
// @@protoc_insertion_point(message:user_data)
pub struct User_data {
    // message fields
    // @@protoc_insertion_point(field:user_data.sensor_1)
    pub sensor_1: i32,
    // @@protoc_insertion_point(field:user_data.sensor_2)
    pub sensor_2: f64,
    // @@protoc_insertion_point(field:user_data.sensor_3)
    pub sensor_3: bool,
    // special fields
    // @@protoc_insertion_point(special_field:user_data.special_fields)
    pub special_fields: ::protobuf::SpecialFields,
}

impl<'a> ::std::default::Default for &'a User_data {
    fn default() -> &'a User_data {
        <User_data as ::protobuf::Message>::default_instance()
    }
}

impl User_data {
    pub fn new() -> User_data {
        ::std::default::Default::default()
    }

    fn generated_message_descriptor_data() -> ::protobuf::reflect::GeneratedMessageDescriptorData {
        let mut fields = ::std::vec::Vec::with_capacity(3);
        let mut oneofs = ::std::vec::Vec::with_capacity(0);
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "sensor_1",
            |m: &User_data| { &m.sensor_1 },
            |m: &mut User_data| { &mut m.sensor_1 },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "sensor_2",
            |m: &User_data| { &m.sensor_2 },
            |m: &mut User_data| { &mut m.sensor_2 },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "sensor_3",
            |m: &User_data| { &m.sensor_3 },
            |m: &mut User_data| { &mut m.sensor_3 },
        ));
        ::protobuf::reflect::GeneratedMessageDescriptorData::new_2::<User_data>(
            "user_data",
            fields,
            oneofs,
        )
    }
}

impl ::protobuf::Message for User_data {
    const NAME: &'static str = "user_data";

    fn is_initialized(&self) -> bool {
        true
    }

    fn merge_from(&mut self, is: &mut ::protobuf::CodedInputStream<'_>) -> ::protobuf::Result<()> {
        while let Some(tag) = is.read_raw_tag_or_eof()? {
            match tag {
                8 => {
                    self.sensor_1 = is.read_int32()?;
                },
                17 => {
                    self.sensor_2 = is.read_double()?;
                },
                24 => {
                    self.sensor_3 = is.read_bool()?;
                },
                tag => {
                    ::protobuf::rt::read_unknown_or_skip_group(tag, is, self.special_fields.mut_unknown_fields())?;
                },
            };
        }
        ::std::result::Result::Ok(())
    }

    // Compute sizes of nested messages
    #[allow(unused_variables)]
    fn compute_size(&self) -> u64 {
        let mut my_size = 0;
        if self.sensor_1 != 0 {
            my_size += ::protobuf::rt::int32_size(1, self.sensor_1);
        }
        if self.sensor_2 != 0. {
            my_size += 1 + 8;
        }
        if self.sensor_3 != false {
            my_size += 1 + 1;
        }
        my_size += ::protobuf::rt::unknown_fields_size(self.special_fields.unknown_fields());
        self.special_fields.cached_size().set(my_size as u32);
        my_size
    }

    fn write_to_with_cached_sizes(&self, os: &mut ::protobuf::CodedOutputStream<'_>) -> ::protobuf::Result<()> {
        if self.sensor_1 != 0 {
            os.write_int32(1, self.sensor_1)?;
        }
        if self.sensor_2 != 0. {
            os.write_double(2, self.sensor_2)?;
        }
        if self.sensor_3 != false {
            os.write_bool(3, self.sensor_3)?;
        }
        os.write_unknown_fields(self.special_fields.unknown_fields())?;
        ::std::result::Result::Ok(())
    }

    fn special_fields(&self) -> &::protobuf::SpecialFields {
        &self.special_fields
    }

    fn mut_special_fields(&mut self) -> &mut ::protobuf::SpecialFields {
        &mut self.special_fields
    }

    fn new() -> User_data {
        User_data::new()
    }

    fn clear(&mut self) {
        self.sensor_1 = 0;
        self.sensor_2 = 0.;
        self.sensor_3 = false;
        self.special_fields.clear();
    }

    fn default_instance() -> &'static User_data {
        static instance: User_data = User_data {
            sensor_1: 0,
            sensor_2: 0.,
            sensor_3: false,
            special_fields: ::protobuf::SpecialFields::new(),
        };
        &instance
    }
}

impl ::protobuf::MessageFull for User_data {
    fn descriptor() -> ::protobuf::reflect::MessageDescriptor {
        static descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::MessageDescriptor> = ::protobuf::rt::Lazy::new();
        descriptor.get(|| file_descriptor().message_by_package_relative_name("user_data").unwrap()).clone()
    }
}

impl ::std::fmt::Display for User_data {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        ::protobuf::text_format::fmt(self, f)
    }
}

impl ::protobuf::reflect::ProtobufValue for User_data {
    type RuntimeType = ::protobuf::reflect::rt::RuntimeTypeMessage<Self>;
}

#[derive(PartialEq,Clone,Default,Debug)]
// @@protoc_insertion_point(message:Payload)
pub struct Payload {
    // message fields
    // @@protoc_insertion_point(field:Payload.sign)
    pub sign: ::std::vec::Vec<u8>,
    // @@protoc_insertion_point(field:Payload.type)
    pub type_: ::protobuf::EnumOrUnknown<payload::UserDataType>,
    // @@protoc_insertion_point(field:Payload.user)
    pub user: ::std::vec::Vec<u8>,
    // special fields
    // @@protoc_insertion_point(special_field:Payload.special_fields)
    pub special_fields: ::protobuf::SpecialFields,
}

impl<'a> ::std::default::Default for &'a Payload {
    fn default() -> &'a Payload {
        <Payload as ::protobuf::Message>::default_instance()
    }
}

impl Payload {
    pub fn new() -> Payload {
        ::std::default::Default::default()
    }

    fn generated_message_descriptor_data() -> ::protobuf::reflect::GeneratedMessageDescriptorData {
        let mut fields = ::std::vec::Vec::with_capacity(3);
        let mut oneofs = ::std::vec::Vec::with_capacity(0);
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "sign",
            |m: &Payload| { &m.sign },
            |m: &mut Payload| { &mut m.sign },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "type",
            |m: &Payload| { &m.type_ },
            |m: &mut Payload| { &mut m.type_ },
        ));
        fields.push(::protobuf::reflect::rt::v2::make_simpler_field_accessor::<_, _>(
            "user",
            |m: &Payload| { &m.user },
            |m: &mut Payload| { &mut m.user },
        ));
        ::protobuf::reflect::GeneratedMessageDescriptorData::new_2::<Payload>(
            "Payload",
            fields,
            oneofs,
        )
    }
}

impl ::protobuf::Message for Payload {
    const NAME: &'static str = "Payload";

    fn is_initialized(&self) -> bool {
        true
    }

    fn merge_from(&mut self, is: &mut ::protobuf::CodedInputStream<'_>) -> ::protobuf::Result<()> {
        while let Some(tag) = is.read_raw_tag_or_eof()? {
            match tag {
                10 => {
                    self.sign = is.read_bytes()?;
                },
                16 => {
                    self.type_ = is.read_enum_or_unknown()?;
                },
                26 => {
                    self.user = is.read_bytes()?;
                },
                tag => {
                    ::protobuf::rt::read_unknown_or_skip_group(tag, is, self.special_fields.mut_unknown_fields())?;
                },
            };
        }
        ::std::result::Result::Ok(())
    }

    // Compute sizes of nested messages
    #[allow(unused_variables)]
    fn compute_size(&self) -> u64 {
        let mut my_size = 0;
        if !self.sign.is_empty() {
            my_size += ::protobuf::rt::bytes_size(1, &self.sign);
        }
        if self.type_ != ::protobuf::EnumOrUnknown::new(payload::UserDataType::JSON) {
            my_size += ::protobuf::rt::int32_size(2, self.type_.value());
        }
        if !self.user.is_empty() {
            my_size += ::protobuf::rt::bytes_size(3, &self.user);
        }
        my_size += ::protobuf::rt::unknown_fields_size(self.special_fields.unknown_fields());
        self.special_fields.cached_size().set(my_size as u32);
        my_size
    }

    fn write_to_with_cached_sizes(&self, os: &mut ::protobuf::CodedOutputStream<'_>) -> ::protobuf::Result<()> {
        if !self.sign.is_empty() {
            os.write_bytes(1, &self.sign)?;
        }
        if self.type_ != ::protobuf::EnumOrUnknown::new(payload::UserDataType::JSON) {
            os.write_enum(2, ::protobuf::EnumOrUnknown::value(&self.type_))?;
        }
        if !self.user.is_empty() {
            os.write_bytes(3, &self.user)?;
        }
        os.write_unknown_fields(self.special_fields.unknown_fields())?;
        ::std::result::Result::Ok(())
    }

    fn special_fields(&self) -> &::protobuf::SpecialFields {
        &self.special_fields
    }

    fn mut_special_fields(&mut self) -> &mut ::protobuf::SpecialFields {
        &mut self.special_fields
    }

    fn new() -> Payload {
        Payload::new()
    }

    fn clear(&mut self) {
        self.sign.clear();
        self.type_ = ::protobuf::EnumOrUnknown::new(payload::UserDataType::JSON);
        self.user.clear();
        self.special_fields.clear();
    }

    fn default_instance() -> &'static Payload {
        static instance: Payload = Payload {
            sign: ::std::vec::Vec::new(),
            type_: ::protobuf::EnumOrUnknown::from_i32(0),
            user: ::std::vec::Vec::new(),
            special_fields: ::protobuf::SpecialFields::new(),
        };
        &instance
    }
}

impl ::protobuf::MessageFull for Payload {
    fn descriptor() -> ::protobuf::reflect::MessageDescriptor {
        static descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::MessageDescriptor> = ::protobuf::rt::Lazy::new();
        descriptor.get(|| file_descriptor().message_by_package_relative_name("Payload").unwrap()).clone()
    }
}

impl ::std::fmt::Display for Payload {
    fn fmt(&self, f: &mut ::std::fmt::Formatter<'_>) -> ::std::fmt::Result {
        ::protobuf::text_format::fmt(self, f)
    }
}

impl ::protobuf::reflect::ProtobufValue for Payload {
    type RuntimeType = ::protobuf::reflect::rt::RuntimeTypeMessage<Self>;
}

/// Nested message and enums of message `Payload`
pub mod payload {
    #[derive(Clone,Copy,PartialEq,Eq,Debug,Hash)]
    // @@protoc_insertion_point(enum:Payload.UserDataType)
    pub enum UserDataType {
        // @@protoc_insertion_point(enum_value:Payload.UserDataType.JSON)
        JSON = 0,
        // @@protoc_insertion_point(enum_value:Payload.UserDataType.PB)
        PB = 1,
        // @@protoc_insertion_point(enum_value:Payload.UserDataType.RAW)
        RAW = 2,
    }

    impl ::protobuf::Enum for UserDataType {
        const NAME: &'static str = "UserDataType";

        fn value(&self) -> i32 {
            *self as i32
        }

        fn from_i32(value: i32) -> ::std::option::Option<UserDataType> {
            match value {
                0 => ::std::option::Option::Some(UserDataType::JSON),
                1 => ::std::option::Option::Some(UserDataType::PB),
                2 => ::std::option::Option::Some(UserDataType::RAW),
                _ => ::std::option::Option::None
            }
        }

        const VALUES: &'static [UserDataType] = &[
            UserDataType::JSON,
            UserDataType::PB,
            UserDataType::RAW,
        ];
    }

    impl ::protobuf::EnumFull for UserDataType {
        fn enum_descriptor() -> ::protobuf::reflect::EnumDescriptor {
            static descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::EnumDescriptor> = ::protobuf::rt::Lazy::new();
            descriptor.get(|| super::file_descriptor().enum_by_package_relative_name("Payload.UserDataType").unwrap()).clone()
        }

        fn descriptor(&self) -> ::protobuf::reflect::EnumValueDescriptor {
            let index = *self as usize;
            Self::enum_descriptor().value_by_index(index)
        }
    }

    impl ::std::default::Default for UserDataType {
        fn default() -> Self {
            UserDataType::JSON
        }
    }

    impl UserDataType {
        pub(in super) fn generated_enum_descriptor_data() -> ::protobuf::reflect::GeneratedEnumDescriptorData {
            ::protobuf::reflect::GeneratedEnumDescriptorData::new::<UserDataType>("Payload.UserDataType")
        }
    }
}

static file_descriptor_proto_data: &'static [u8] = b"\
    \n\x13protos/upload.proto\"\\\n\tuser_data\x12\x19\n\x08sensor_1\x18\x01\
    \x20\x01(\x05R\x07sensor1\x12\x19\n\x08sensor_2\x18\x02\x20\x01(\x01R\
    \x07sensor2\x12\x19\n\x08sensor_3\x18\x03\x20\x01(\x08R\x07sensor3\"\x87\
    \x01\n\x07Payload\x12\x12\n\x04sign\x18\x01\x20\x01(\x0cR\x04sign\x12)\n\
    \x04type\x18\x02\x20\x01(\x0e2\x15.Payload.UserDataTypeR\x04type\x12\x12\
    \n\x04user\x18\x03\x20\x01(\x0cR\x04user\")\n\x0cUserDataType\x12\x08\n\
    \x04JSON\x10\0\x12\x06\n\x02PB\x10\x01\x12\x07\n\x03RAW\x10\x02b\x06prot\
    o3\
";

/// `FileDescriptorProto` object which was a source for this generated file
fn file_descriptor_proto() -> &'static ::protobuf::descriptor::FileDescriptorProto {
    static file_descriptor_proto_lazy: ::protobuf::rt::Lazy<::protobuf::descriptor::FileDescriptorProto> = ::protobuf::rt::Lazy::new();
    file_descriptor_proto_lazy.get(|| {
        ::protobuf::Message::parse_from_bytes(file_descriptor_proto_data).unwrap()
    })
}

/// `FileDescriptor` object which allows dynamic access to files
pub fn file_descriptor() -> &'static ::protobuf::reflect::FileDescriptor {
    static generated_file_descriptor_lazy: ::protobuf::rt::Lazy<::protobuf::reflect::GeneratedFileDescriptor> = ::protobuf::rt::Lazy::new();
    static file_descriptor: ::protobuf::rt::Lazy<::protobuf::reflect::FileDescriptor> = ::protobuf::rt::Lazy::new();
    file_descriptor.get(|| {
        let generated_file_descriptor = generated_file_descriptor_lazy.get(|| {
            let mut deps = ::std::vec::Vec::with_capacity(0);
            let mut messages = ::std::vec::Vec::with_capacity(2);
            messages.push(User_data::generated_message_descriptor_data());
            messages.push(Payload::generated_message_descriptor_data());
            let mut enums = ::std::vec::Vec::with_capacity(1);
            enums.push(payload::UserDataType::generated_enum_descriptor_data());
            ::protobuf::reflect::GeneratedFileDescriptor::new_generated(
                file_descriptor_proto(),
                deps,
                messages,
                enums,
            )
        });
        ::protobuf::reflect::FileDescriptor::new_generated_2(generated_file_descriptor)
    })
}
