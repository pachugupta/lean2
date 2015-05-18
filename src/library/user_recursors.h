/*
Copyright (c) 2015 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#pragma once

namespace lean {
/** \brief Information for a user defined recursor */
class recursor_info {
    name               m_recursor;
    name               m_type_name;
    optional<unsigned> m_motive_univ_pos; // if none, then recursor can only eliminate to Prop
    bool               m_dep_elim;
    unsigned           m_major_pos;
    list<unsigned>     m_params_pos; // position of the recursor parameters in the major premise
    list<unsigned>     m_indices_pos; // position of the recursor indices in the major premise

public:
    recursor_info(name const & r, name const & I,
                  optional<unsigned> const & motive_univ_pos,
                  bool dep_elim,
                  unsigned major_pos,
                  list<unsigned> const & params_pos,
                  list<unsigned> const & indices_pos);
    recursor_info();

    name const & get_name() const { return m_recursor; }
    name const & get_type_name() const { return m_type_name; }
    unsigned get_num_params() const { return length(m_params_pos); }
    unsigned get_num_indices() const { return length(m_indices_pos); }
    unsigned get_motive_pos() const { return get_num_params(); }
    unsigned get_first_index_pos() const { return m_major_pos - get_num_indices(); }
    unsigned get_major_pos() const { return m_major_pos; }
    optional<unsigned> const & get_motive_univ_pos() const { return m_motive_univ_pos; }
    /** \brief Return position of the recursor parameters in the major premise. */
    list<unsigned> const & get_params_pos() const { return m_params_pos; }
    /** \brief Return position of the recursor indices in the major premise. */
    list<unsigned> const & get_indices_pos() const { return m_indices_pos; }
    bool has_dep_elim() const { return m_dep_elim; }
    bool is_minor(unsigned pos) const;

    void write(serializer & s) const;
    static recursor_info read(deserializer & d);
};

environment add_user_recursor(environment const & env, name const & r, optional<unsigned> const & major_pos, bool persistent);
recursor_info get_recursor_info(environment const & env, name const & r);
list<name> get_recursors_for(environment const & env, name const & I);

class has_recursors_pred {
    name_map<list<name>>    m_type2recursors;
public:
    has_recursors_pred(environment const & env);
    bool operator()(name const & n) const { return m_type2recursors.contains(n); }
};

void initialize_user_recursors();
void finalize_user_recursors();
}