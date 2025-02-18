#pragma once

#define GENERIC(Name, T) Name##_##T
#define GENERIC2(Name, T1, T2) Name##_##T1##_##T2
#define GENERIC3(Name, T1, T2, T3) Name##_##T1##_##T2##_##T3
#define GENERIC4(Name, T1, T2, T3, T4) Name##_##T1##_##T2##_##T3##_##T4
#define GENERIC5(Name, T1, T2, T3, T4, T5) Name##_##T1##_##T2##_##T3##_##T4##_##T5
#define GENERIC6(Name, T1, T2, T3, T4, T5, T6) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6
#define GENERIC7(Name, T1, T2, T3, T4, T5, T6, T7) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7
#define GENERIC8(Name, T1, T2, T3, T4, T5, T6, T7, T8) Name##_##T1##_##T2##_##T3##_##T4##_##T5##_##T6##_##T7##_##T8
