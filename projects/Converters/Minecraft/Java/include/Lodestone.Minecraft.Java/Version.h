//
// Created by DexrnZacAttack on 10/25/25 using zPc-i2.
//
#ifndef LODESTONE_JAVA_VERSION_H
#define LODESTONE_JAVA_VERSION_H


#include <cstdint>

// NOLINTBEGIN(readability-identifier-naming)
//shut up
namespace lodestone::minecraft::java {

#define X_TO_ENUM(name) name,

#define ENUM_PRE_CLASSIC_STAGE(X) \
    X(rd131655)               \
    X(rd132211)                \
    X(rd132328)                \
    X(rd20090515)              \
    X(rd160052)                \
    X(rd161348)

#define ENUM_CLASSIC_STAGE(X) \
    X(c0_0_2a)                \
    X(c0_0_3a)                \
    X(c0_0_9a)                \
    X(c0_0_10a)               \
    X(c0_0_11a)               \
    X(c0_0_12a)               \
    X(c0_0_12a_01)            \
    X(c0_0_12a_02)            \
    X(c0_0_12a_03)            \
    X(c0_0_13a)               \
    X(c0_0_13a_03)            \
    X(c0_0_14a)               \
    X(c0_0_14a_01)            \
    X(c0_0_14a_03)            \
    X(c0_0_14a_04)            \
    X(c0_0_14a_05)            \
    X(c0_0_14a_06)            \
    X(c0_0_14a_07)            \
    X(c0_0_14a_08)            \
    X(c0_0_15a)               \
    X(c0_0_15a_mp2) /*mp test 2*/               \
    X(c0_0_15a_mp3) /*mp test 3*/               \
    X(c0_0_15a_mp4) /*mp test 4*/               \
    X(c0_0_15a_mp5) /*mp test 5*/               \
    X(c0_0_15a_mp6) /*mp test 6*/               \
    X(c0_0_15a_mp7) /*mp test 7*/               \
    X(c0_0_15a_mp8) /*mp test 8*/               \
    X(c0_0_15a_01)             \
    X(c0_0_15a_02)             \
    X(c0_0_15a_03)             \
    X(c0_0_16a)             \
    X(c0_0_16a_01)             \
    X(c0_0_16a_02)             \
    X(c0_0_17a)             \
    X(c0_0_18a)             \
    X(c0_0_18a_01)             \
    X(c0_0_18a_02)             \
    X(c0_0_19a)             \
    X(c0_0_19a_01) /*TODO glass No longer semi transparent.*/               \
    X(c0_0_19a_02)             \
    X(c0_0_19a_03)             \
    X(c0_0_19a_04)             \
    X(c0_0_19a_05)             \
    X(c0_0_19a_06)             \
    X(c0_0_20a)             \
    X(c0_0_20a_01)             \
    X(c0_0_20a_02)             \
    X(c0_0_21a)             \
    X(c0_0_21a_01)             \
    X(c0_0_22a)             \
    X(c0_0_22a_01)             \
    X(c0_0_22a_02)             \
    X(c0_0_22a_03)             \
    X(c0_0_22a_04)             \
    X(c0_0_22a_05)             \
    X(c0_0_23a)             \
    X(c0_0_23a_01)             \
    X(c0_24st) /*survival test*/               \
    X(c0_24st_01)             \
    X(c0_24st_02)             \
    X(c0_24st_03)             \
    X(c0_25st)             \
    X(c0_25st_02)             \
    X(c0_25st_03)             \
    X(c0_25st_04)             \
    X(c0_25st_05)             \
    X(c0_26st)             \
    X(c0_27st)             \
    X(c0_28)             \
    X(c0_28_01)             \
    X(c0_29)             \
    X(c0_29_01)             \
    X(c0_29_02)             \
    X(c0_30) /*survival*/               \
    X(c0_30_01) /*creative*/               \
    X(c0_30_CPE) /*specifically for classic protocol extensions, which adds additional blocks not seen normally, TODO we should move this when classicextensions module comes. */

#define ENUM_INDEV_STAGE(X) \
    X(in20091223_1457) \
    X(in20100109_1939) \
    X(in20100114) \
    X(in20100122_2251) \
    X(in20100124_2119) \
    X(in20100128_2200) \
    X(in20100129_2332) \
    X(in20100206_2034) \
    X(in20100219)

#define ENUM_INFDEV_STAGE(X) \
    X(inf20100607) \
    X(inf20100618) \
    X(inf20100624) \
    X(inf20100625_1917) \
    X(inf20100629)

#define ENUM_ALPHA_STAGE(X) \
    X(a1_0_1) \
    X(a1_0_4) \
    X(a1_0_5) \
    X(a1_0_6) \
    X(a1_0_11) \
    X(a1_0_14) \
    X(a1_0_17) \
    X(a1_2_0)

#define ENUM_BETA_STAGE(X) \
    X(b1_1) \
    X(b1_2) \
    X(b1_3) /*FORMAT CHANGE*/ \
    X(b1_4) \
    X(b1_5) \
    X(b1_6) \
    X(b1_7) \
    X(b1_8) \
    X(b1_9_pr1) \
    X(b1_9_pr2) \
    X(b1_9_pr3) \
    X(b1_9_pr4) \
    X(b1_9_pr6)

#define ENUM_RELEASE_STAGE(X) \
    X(r1_2_1)

#define ENUM_FLATTENED_STAGE(X)
#define ENUM_GAMMA_STAGE(X)

    enum class Version : std::uint32_t {
        ENUM_PRE_CLASSIC_STAGE(X_TO_ENUM)
        ENUM_CLASSIC_STAGE(X_TO_ENUM)
        ENUM_INDEV_STAGE(X_TO_ENUM)
        ENUM_INFDEV_STAGE(X_TO_ENUM)
        ENUM_ALPHA_STAGE(X_TO_ENUM)
        ENUM_BETA_STAGE(X_TO_ENUM)
        ENUM_RELEASE_STAGE(X_TO_ENUM)
        ENUM_FLATTENED_STAGE(X_TO_ENUM)
        ENUM_GAMMA_STAGE(X_TO_ENUM)
    };

#undef X_TO_ENUM
#define X_TO_ENUM(name) name = static_cast<int>(Version::name),

#define X_TO_ENUM_CLASS(clazz, name)  \
    enum class clazz : std::uint32_t {                \
        name(X_TO_ENUM)               \
    }   \

    X_TO_ENUM_CLASS(PreClassicStage, ENUM_PRE_CLASSIC_STAGE);
    X_TO_ENUM_CLASS(ClassicStage, ENUM_CLASSIC_STAGE);
    X_TO_ENUM_CLASS(IndevStage, ENUM_INDEV_STAGE);
    X_TO_ENUM_CLASS(InfdevStage, ENUM_INFDEV_STAGE);
    X_TO_ENUM_CLASS(AlphaStage, ENUM_ALPHA_STAGE);
    X_TO_ENUM_CLASS(BetaStage, ENUM_BETA_STAGE);
    X_TO_ENUM_CLASS(ReleaseStage, ENUM_RELEASE_STAGE);
    X_TO_ENUM_CLASS(FlattenedStage, ENUM_FLATTENED_STAGE);
    X_TO_ENUM_CLASS(GammaStage, ENUM_GAMMA_STAGE);//when they switched to yy.m version numbering

#undef X_TO_ENUM
}

// NOLINTEND(readability-identifier-naming)

#endif // LODESTONE_VERSION_H
