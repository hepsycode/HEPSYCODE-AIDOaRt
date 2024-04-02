package transformationTest;

import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.IWorkbenchWindowActionDelegate;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.swt.widgets.Shell;


/** Model2TextAction is a simple example of using an
 * action set to extend the Eclipse Workbench with a menu 
 * and toolbar action that prints the "Hello World" message.
 */

public class Model2TextAction implements IWorkbenchWindowActionDelegate {
	IWorkbenchWindow activeWindow = null;

	@SuppressWarnings("unused")
	@Override
	public void run(IAction proxyAction) {
		// proxyAction has UI information from manifest file (ignored)
		Shell shell = activeWindow.getShell();
		MessageDialog.openInformation(shell, "HepsyCode", "HepsyCode");
	}

	@Override
	public void selectionChanged(IAction proxyAction, ISelection selection) {
		// TODO Auto-generated method stub

	}
	
	@Override
	public void init(IWorkbenchWindow window) {
		// TODO Auto-generated method stub
		activeWindow = window;

	}
	
	@Override
	public void dispose() {
		// TODO Auto-generated method stub

	}


}
