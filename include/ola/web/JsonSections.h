/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * JsonSections.h
 * This builds the json string for the web UI.
 * Copyright (C) 2010 Simon Newton
 */

#ifndef INCLUDE_OLA_WEB_JSONSECTIONS_H_
#define INCLUDE_OLA_WEB_JSONSECTIONS_H_

#include <ola/StringUtils.h>
#include <ola/web/Json.h>
#include <string>
#include <utility>
#include <vector>

namespace ola {
namespace web {

using std::string;

/**
 * This is the base item class. Items are composed into sections.
 * Each item has the following:
 *  - A text description
 *  - A type, which controls how the item is renders
 *  - The value.
 *  - Optional id. A non-empty id makes this item editable
 *  - Optional button text. Non-empty means this item get's it own button.
 */
class GenericItem {
  public:
    GenericItem(const string &description, const string &id):
        m_description(description),
        m_id(id),
        m_button_text("") {
    }
    virtual ~GenericItem() {}

    // Sets the text for the button associated
    void SetButtonText(const string &text) {
      m_button_text = text;
    }

    void PopulateItem(JsonObject *item) const;

  protected:
    virtual string Type() const = 0;
    virtual void SetValue(JsonObject *item) const = 0;
    virtual void SetExtraProperties(JsonObject *item) const {
      (void) item;
    }

  private:
    string m_description;
    string m_id;
    string m_button_text;
};


/*
 * This is a item that contains a string value
 */
class StringItem: public GenericItem {
  public:
    StringItem(const string &description,
               const string &value,
               const string &id = ""):
      GenericItem(description, id),
      m_value(value) {
    }

  protected:
    string Type() const { return "string"; }
    void SetValue(JsonObject *item) const {
      item->Add("value", m_value);
    }

  private:
    string m_value;
};


/*
 * An item that contains a unsigned int
 */
class UIntItem: public GenericItem {
  public:
    UIntItem(const string &description,
             unsigned int value,
             const string &id = ""):
      GenericItem(description, id),
      m_value(value),
      m_min_set(false),
      m_max_set(false) {
    }

    void SetMin(unsigned int min) {
      m_min_set = true;
      m_min = min;
    }
    void SetMax(unsigned int max) {
      m_max_set = true;
      m_max = max;
    }

  protected:
    void SetExtraProperties(JsonObject *item) const;
    string Type() const { return "uint"; }
    void SetValue(JsonObject *item) const {
      item->Add("value", m_value);
    }

  private:
    unsigned int m_value;
    bool m_min_set, m_max_set;
    unsigned int m_min;
    unsigned int m_max;
};


class BoolItem: public GenericItem {
  public:
    BoolItem(const string &description,
             bool value,
             const string &id):
      GenericItem(description, id),
      m_value(value) {
    }

  protected:
    string Type() const { return "bool"; }
    void SetValue(JsonObject *item) const {
      item->Add("value", m_value);
    }

  private:
    bool m_value;
};


class HiddenItem: public GenericItem {
  public:
    HiddenItem(const string &value, const string &id):
      GenericItem("", id),
      m_value(value) {
    }

  protected:
    string Type() const { return "hidden"; }
    void SetValue(JsonObject *item) const {
      item->Add("value", m_value);
    }

  private:
    string m_value;
};


/*
 * An item which is a select list
 */
class SelectItem: public GenericItem {
  public:
    SelectItem(const string &description,
               const string &id = ""):
      GenericItem(description, id),
      m_selected_offset(0) {
    }

    void SetSelectedOffset(unsigned int offset) { m_selected_offset = offset; }
    void AddItem(const string &label, const string &value);
    // helper method which converts ints to strings
    void AddItem(const string &label, unsigned int value);

  protected:
    void SetExtraProperties(JsonObject *item) const {
      item->Add("selected_offset", m_selected_offset);
    }
    string Type() const { return "select"; }
    void SetValue(JsonObject *item) const;

  private:
    std::vector<std::pair<string, string> > m_values;
    unsigned int m_selected_offset;
};


class JsonSection {
  public:
    explicit JsonSection(bool allow_refresh = true);
    ~JsonSection();

    void SetSaveButton(const string &text) { m_save_button_text = text; }
    void SetError(const string &error) { m_error = error; }

    void AddItem(const GenericItem *item);
    string AsString() const;

  private:
    bool m_allow_refresh;
    string m_error;
    string m_save_button_text;
    std::vector<const GenericItem*> m_items;
};
}  // namespace web
}  // namespace ola
#endif  // INCLUDE_OLA_WEB_JSONSECTIONS_H_
