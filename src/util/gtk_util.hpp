#pragma once
#include <gtkmm.h>
#include <stdint.h>
namespace horizon {
void bind_widget(class SpinButtonDim *sp, int64_t &v);
void bind_widget(class SpinButtonDim *sp, uint64_t &v);

void bind_widget(Gtk::Switch *sw, bool &v);
void bind_widget(Gtk::CheckButton *sw, bool &v);
void bind_widget(Gtk::SpinButton *sp, int &v);
void bind_widget(Gtk::Scale *sc, float &v);
void bind_widget(Gtk::Entry *en, std::string &v, std::function<void(std::string &v)> extra_cb = nullptr);
void bind_widget(Gtk::ColorButton *color_button, class Color &color,
                 std::function<void(const Color &c)> extra_cb = nullptr);

template <typename T>
void bind_widget(std::map<T, Gtk::RadioButton *> &widgets, T &v, std::function<void(T)> extra_cb = nullptr)
{
    widgets[v]->set_active(true);
    for (auto &it : widgets) {
        T key = it.first;
        Gtk::RadioButton *w = it.second;
        it.second->signal_toggled().connect([key, w, &v, extra_cb] {
            if (w->get_active()) {
                v = key;
                if (extra_cb)
                    extra_cb(key);
            }
        });
    }
}

template <typename T>
void bind_widget(Gtk::ComboBoxText *combo, const std::map<T, std::string> &lut, T &v,
                 std::function<void(T)> extra_cb = nullptr)
{
    for (const auto &it : lut) {
        combo->append(std::to_string(static_cast<int>(it.first)), it.second);
    }
    combo->set_active_id(std::to_string(static_cast<int>(v)));
    combo->signal_changed().connect([combo, &v, extra_cb] {
        v = static_cast<T>(std::stoi(combo->get_active_id()));
        if (extra_cb)
            extra_cb(v);
    });
}

Gtk::Label *grid_attach_label_and_widget(Gtk::Grid *gr, const std::string &label, Gtk::Widget *w, int &top);
void label_set_tnum(Gtk::Label *la);

void tree_view_scroll_to_selection(Gtk::TreeView *view);
void entry_set_warning(Gtk::Entry *e, const std::string &text);

void header_func_separator(Gtk::ListBoxRow *row, Gtk::ListBoxRow *before);

void entry_add_sanitizer(Gtk::Entry *entry);

void info_bar_show(Gtk::InfoBar *bar);
void info_bar_hide(Gtk::InfoBar *bar);

} // namespace horizon
