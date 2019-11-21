#include <criterion/criterion.h>
#include <criterion/logging.h>

int simple_func(int a)
{
	return (-a);
}

Test(suite_name, test_name) {
	cr_assert(simple_func(-1) == 2, "test rapido");
	cr_log_info("This is an informational message. They are not displayed "
			"by default.");
	cr_log_warn("This is a warning. They indicate some possible malfunction "
			"or misconfiguration in the test.");
	cr_log_error("This is an error. They indicate serious problems and "
			"are usually shown before the test is aborted.");
}
