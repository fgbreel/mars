// (c) 2010 Thomas Schoebel-Theuer / 1&1 Internet AG
struct if_device_brick {
	MARS_BRICK(if_device);
};

struct if_device_input {
	MARS_INPUT(if_device);
	struct request_queue *q;
	struct gendisk *disk;
	struct block_device *bdev;
	int mio_size;
};

struct if_device_output {
	MARS_OUTPUT(if_device);
};

MARS_TYPES(if_device);
