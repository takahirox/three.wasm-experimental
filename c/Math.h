#ifndef __THREE_MATH_H__
#define __THREE_MATH_H__

struct LinkedList {
	struct LinkedList *next;
	struct LinkedList *prev;
	void *value;
};

struct LinkedListHeader {
	struct LinkedList *head;
	struct LinkedList *tail;
};

struct Vector3 {
	double x;
	double y;
	double z;
};

struct Quaternion {
	double x;
	double y;
	double z;
	double w;
};

struct Euler {
	double x;
	double y;
	double z;
	int order;
	int dummy;
};

struct Matrix3 {
	double elements[9];
};

struct Matrix4 {
	double elements[16];
};

struct LinkedList* LinkedList_new(
	void *value
);

struct LinkedListHeader* LinkedListHeader_init(
	struct LinkedListHeader *self
);

struct LinkedListHeader* LinkedListHeader_add(
	struct LinkedListHeader *self,
	void *value
);

struct Vector3* Vector3_init(
	struct Vector3 *self
);

struct Vector3* Vector3_copy(
	struct Vector3 *self,
	struct Vector3 *v
);

int Vector3_equals(
	struct Vector3 *self,
	struct Vector3 *v
);

struct Vector3* Vector3_applyMatrix4(
	struct Vector3 *self,
	struct Matrix4 *m
);

struct Quaternion* Quaternion_init(
	struct Quaternion *self
);

int Quaternion_equals(
	struct Quaternion *self,
	struct Quaternion *q
);

struct Quaternion* Quaternion_copy(
	struct Quaternion *self,
	struct Quaternion *q
);

struct Quaternion* Quaternion_setFromEuler(
	struct Quaternion *self,
	struct Euler *euler
);

struct Euler* Euler_init(
	struct Euler *self
);

struct Matrix3* Matrix3_init(
	struct Matrix3 *self
);

struct Matrix3* Matrix3_setFromMatrix4(
	struct Matrix3 *self,
	struct Matrix4 *m
);

struct Matrix3* Matrix3_getInverse(
	struct Matrix3 *self,
	struct Matrix3 *matrix
);

struct Matrix3* Matrix3_transpose(
	struct Matrix3 *self
);

struct Matrix3* Matrix3_getNormalMatrix(
	struct Matrix3 *self,
	struct Matrix4 *matrix4
);

struct Matrix4* Matrix4_init(
	struct Matrix4 *self
);

struct Matrix4* Matrix4_compose(
	struct Matrix4 *self,
	struct Vector3 *position,
	struct Quaternion *quaternion,
	struct Vector3 *scale
);

struct Matrix4* Matrix4_copy(
	struct Matrix4 *self,
	struct Matrix4 *m
);

struct Matrix4* Matrix4_multiplyMatrices(
	struct Matrix4 *self,
	struct Matrix4 *a,
	struct Matrix4 *b
);

#endif
