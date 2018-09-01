#ifndef KOYO_DATA_LIST_H
#define KOYO_DATA_LIST_H

namespace koyo {
	namespace data_list {
		// for input
		struct signal {
			double vartical;   // c•ûŒü
			double horizontal; // ‰ñ“]•ûŒü
			bool button0;      // ƒ{ƒ^ƒ“
		};

		// for output
		struct command {
			double vel;    // ‘¬“x
			double omega;  // Šp‘¬“x
			double weapon; // UŒ‚
		};
	}
}

#endif