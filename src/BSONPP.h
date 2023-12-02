#ifndef __BSONPP_H__
#define __BSONPP_H__

#include <stdint.h>

enum BSONPP_ERROR {
  BSONPP_SUCCESS = (0),
  BSONPP_KEY_NOT_FOUND = (-1),
  BSONPP_INCORRECT_TYPE = (-2),
  BSONPP_OUT_OF_SPACE = (-3),
  BSONPP_NO_BUFFER = (-4),
  BSONPP_DUPLICATE_KEY = (-5),
  BSONPP_NULL_VALUE = (-6),
};
enum BSONPP_TYPE {
  BSONPP_INVALID_TYPE = (0x00),
  BSONPP_DOUBLE = (0x01),
  BSONPP_STRING = (0x02),
  BSONPP_DOCUMENT = (0x03),
  BSONPP_ARRAY = (0x04),
  BSONPP_BINARY = (0x05),
  BSONPP_BOOLEAN = (0x08),
  BSONPP_DATETIME = (0x09),
  BSONPP_NULL = (0x0A),
  BSONPP_INT32 = (0x10),
  BSONPP_INT64 = (0x12),
};

#define BSONPP_BINARY_SUBTYPE_GENERIC (0x00)
#define BSONPP_BOOLEAN_FALSE (0x00)
#define BSONPP_BOOLEAN_TRUE (0x01)

class BSONPP {
public:
  BSONPP(uint8_t *buffer, int32_t length, bool clear = true);
  BSONPP();

  int32_t getSize();
  uint8_t *getBuffer();
  int32_t getBufferSize();
  void clear();
  bool exists(const char *key);
  // Various functions for easy iteration.
  BSONPP_ERROR getKeyCount(int32_t *count);
  BSONPP_ERROR getKeyAt(int32_t index, char **key);
  BSONPP_ERROR getTypeAt(int32_t index, BSONPP_TYPE *type);

  BSONPP_ERROR append(const char *key, int32_t val);
  BSONPP_ERROR append(const char *key, int64_t val, bool dateTime = false);
  BSONPP_ERROR append(const char *key, double val);
  BSONPP_ERROR append(const char *key, const char *val);
  BSONPP_ERROR append(const char *key, BSONPP *val, bool isArray = false);
  BSONPP_ERROR append(const char *key, const uint8_t *data, const int32_t length);
  BSONPP_ERROR append(const char *key, bool val);

  int32_t get(const char *key, int32_t *val);
  int32_t get(const char *key, int64_t *val);
  int32_t get(const char *key, double *val);
  int32_t get(const char *key, BSONPP *val);
  int32_t get(const char *key, char **val);
  int32_t get(const char *key, uint8_t **val, int32_t *length = nullptr);
  int32_t get(const char *key, bool *val);

private:
  BSONPP_ERROR appendInternal(const char *key, uint8_t type, const uint8_t *data,
                         int32_t length);
  int32_t getOffset(const char *key, BSONPP_TYPE type = BSONPP_INVALID_TYPE);
  int32_t getOffset(int32_t index);
  void setSize(int32_t size);
  // Type size is inclusive of the length field for variable length values.
  static int32_t getTypeSize(BSONPP_TYPE type, uint8_t *data);
  static BSONPP_TYPE getType(uint8_t *data);
  static uint8_t *getData(uint8_t *data);

  uint8_t *m_buffer;
  int32_t m_length;
};

#endif // __BSONPP_H__
