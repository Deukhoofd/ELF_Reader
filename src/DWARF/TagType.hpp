#ifndef ELF_EXPORTER_TAGTYPE_HPP
#define ELF_EXPORTER_TAGTYPE_HPP

#include <cstdint>
#include <stdexcept>
#include <string>

enum class TagType : uint8_t {
    DW_TAG_compile_unit,
    DW_TAG_structure_type,
    DW_TAG_union_type,
    DW_TAG_enumeration_type,
    DW_TAG_typedef,
    DW_TAG_array_type,
    DW_TAG_subrange_type,
    DW_TAG_inheritance,
    DW_TAG_member,
    DW_TAG_subprogram,
    DW_TAG_formal_parameter,
    DW_TAG_namespace,
    DW_TAG_enumerator,
    DW_TAG_class_type,
    DW_TAG_base_type,
    DW_TAG_pointer_type,
    DW_TAG_const_type,
    DW_TAG_reference_type,
    DW_TAG_template_type_param,
    DW_TAG_template_value_param,
    DW_TAG_GNU_template_parameter_pack,
    DW_TAG_imported_declaration,
    DW_TAG_unspecified_type,
    DW_TAG_rvalue_reference_type,
    DW_TAG_restrict_type,
    DW_TAG_imported_module,
    DW_TAG_unspecified_parameters,
    DW_TAG_subroutine_type,
    DW_TAG_variable,
    DW_TAG_lexical_block,
    DW_TAG_ptr_to_member_type,
    DW_TAG_volatile_type,
    DW_TAG_inlined_subroutine
};

class TagTypeHelper{
    static uint32_t constexpr GetStringHash(char const* input) {
        return *input ? static_cast<uint32_t>(*input) + 33 * GetStringHash(input + 1) : 5381;
    };

public:
    static bool TryParse(std::string s, TagType& out){
        switch(GetStringHash(s.c_str())){
            case GetStringHash("DW_TAG_compile_unit"):
                out = TagType::DW_TAG_compile_unit;
                return true;
            case GetStringHash("DW_TAG_structure_type"):
                out = TagType::DW_TAG_structure_type;
                return true;
            case GetStringHash("DW_TAG_union_type"):
                out = TagType::DW_TAG_union_type;
                return true;
            case GetStringHash("DW_TAG_enumeration_type"):
                out = TagType::DW_TAG_enumeration_type;
                return true;
            case GetStringHash("DW_TAG_typedef"):
                out = TagType::DW_TAG_typedef;
                return true;
            case GetStringHash("DW_TAG_array_type"):
                out = TagType::DW_TAG_array_type;
                return true;
            case GetStringHash("DW_TAG_subrange_type"):
                out = TagType::DW_TAG_subrange_type;
                return true;
            case GetStringHash("DW_TAG_inheritance"):
                out = TagType::DW_TAG_inheritance;
                return true;
            case GetStringHash("DW_TAG_member"):
                out = TagType::DW_TAG_member;
                return true;
            case GetStringHash("DW_TAG_subprogram"):
                out = TagType::DW_TAG_subprogram;
                return true;
            case GetStringHash("DW_TAG_formal_parameter"):
                out = TagType::DW_TAG_formal_parameter;
                return true;
            case GetStringHash("DW_TAG_namespace"):
                out = TagType::DW_TAG_namespace;
                return true;
            case GetStringHash("DW_TAG_enumerator"):
                out = TagType::DW_TAG_enumerator;
                return true;
            case GetStringHash("DW_TAG_class_type"):
                out = TagType::DW_TAG_class_type;
                return true;
            case GetStringHash("DW_TAG_base_type"):
                out = TagType::DW_TAG_base_type;
                return true;
            case GetStringHash("DW_TAG_pointer_type"):
                out = TagType::DW_TAG_pointer_type;
                return true;
            case GetStringHash("DW_TAG_const_type"):
                out = TagType::DW_TAG_const_type;
                return true;
            case GetStringHash("DW_TAG_reference_type"):
                out = TagType::DW_TAG_reference_type;
                return true;
            case GetStringHash("DW_TAG_template_type_param"):
                out = TagType::DW_TAG_template_type_param;
                return true;
            case GetStringHash("DW_TAG_template_value_param"):
                out = TagType::DW_TAG_template_value_param;
                return true;
            case GetStringHash("DW_TAG_GNU_template_parameter_pack"):
                out = TagType::DW_TAG_GNU_template_parameter_pack;
                return true;
            case GetStringHash("DW_TAG_imported_declaration"):
                out = TagType::DW_TAG_imported_declaration;
                return true;
            case GetStringHash("DW_TAG_unspecified_type"):
                out = TagType::DW_TAG_unspecified_type;
                return true;
            case GetStringHash("DW_TAG_rvalue_reference_type"):
                out = TagType::DW_TAG_rvalue_reference_type;
                return true;
            case GetStringHash("DW_TAG_restrict_type"):
                out = TagType::DW_TAG_restrict_type;
                return true;
            case GetStringHash("DW_TAG_imported_module"):
                out = TagType::DW_TAG_imported_module;
                return true;
            case GetStringHash("DW_TAG_unspecified_parameters"):
                out = TagType::DW_TAG_unspecified_parameters;
                return true;
            case GetStringHash("DW_TAG_subroutine_type"):
                out = TagType::DW_TAG_subroutine_type;
                return true;
            case GetStringHash("DW_TAG_variable"):
                out = TagType::DW_TAG_variable;
                return true;
            case GetStringHash("DW_TAG_lexical_block"):
                out = TagType::DW_TAG_lexical_block;
                return true;
            case GetStringHash("DW_TAG_ptr_to_member_type"):
                out = TagType::DW_TAG_ptr_to_member_type;
                return true;
            case GetStringHash("DW_TAG_volatile_type"):
                out = TagType::DW_TAG_volatile_type;
                return true;
            case GetStringHash("DW_TAG_inlined_subroutine"):
                out = TagType::DW_TAG_inlined_subroutine;
                return true;
            default:
                std::cout << "Unknown DW_TAG: '" << s << "'.";
                return false;
        }
    }
};

#endif // ELF_EXPORTER_TAGTYPE_HPP
