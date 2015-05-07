/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBonus.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:25:00 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/07 11:49:05 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GROWBONUS_HPP
# define GROWBONUS_HPP

# include "nibbler.h"
# include "ABlock.hpp"

class	GrowBonus : public ABlock
{
public:
	GrowBonus(void);
	virtual ~GrowBonus(void);

	virtual void			active(Snake &snake);
	virtual bool			shouldDestroy(void) const;

protected:

	bool					_eaten;

private:
	GrowBonus(GrowBonus const &src);
	GrowBonus				&operator=(GrowBonus const &rhs);
};

#endif